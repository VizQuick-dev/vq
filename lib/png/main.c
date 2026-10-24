#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <zlib.h>

#include "vq.h"

int png_unfilter(uint8_t *raw, uint8_t *pixels, int width, int height, int bytes_per_pixel, size_t row_bytes)
{
    for (int y = 0; y < height; y++) {
        uint8_t filter = raw[y * (row_bytes + 1)];
        uint8_t *src = raw + y * (row_bytes + 1) + 1;
        uint8_t *dst = pixels + y * row_bytes;
        uint8_t *prev = y ? pixels + (y - 1) * row_bytes : NULL;

        for (size_t x = 0; x < row_bytes; x++) {
            int a = x >= (size_t)bytes_per_pixel
                  ? dst[x - bytes_per_pixel] : 0;
            int b = prev ? prev[x] : 0;
            int c = prev && x >= (size_t)bytes_per_pixel
                  ? prev[x - bytes_per_pixel] : 0;

            switch (filter) {
                case 0:
                    dst[x] = src[x];
                    break;

                case 1:
                    dst[x] = (uint8_t)(src[x] + a);
                    break;

                case 2:
                    dst[x] = (uint8_t)(src[x] + b);
                    break;

                case 3:
                    dst[x] = (uint8_t)(src[x] + ((a + b) / 2));
                    break;

                case 4: {
                    int p = a + b - c;
                    int pa = abs(p - a);
                    int pb = abs(p - b);
                    int pc = abs(p - c);

                    int pr = pa <= pb && pa <= pc ? a
                           : pb <= pc ? b : c;

                    dst[x] = (uint8_t)(src[x] + pr);
                    break;
                }

                default:
                    return 0;
            }
        }
    }

    return 1;
}

int png_inflate(const uint8_t *idat, size_t idat_size, uint8_t *out, size_t out_size)
{
    z_stream zs = {0};

    if (idat_size > UINT_MAX || out_size > UINT_MAX)
        return Z_STREAM_ERROR;

    zs.next_in = (Bytef *)idat;
    zs.avail_in = (uInt)idat_size;
    zs.next_out = out;
    zs.avail_out = (uInt)out_size;

    int ret = inflateInit(&zs);
    if (ret != Z_OK)
        return ret;

    ret = inflate(&zs, Z_FINISH);

    if (ret == Z_STREAM_END && zs.total_out != out_size)
        ret = Z_DATA_ERROR;

    inflateEnd(&zs);
    return ret;
}

int *vq_png_size(char *buf,size_t size)
{
    int *list = malloc(2 * sizeof(int));

    if (size < 24)
        return NULL;

    const unsigned char *data = (const unsigned char *)buf;

    uint32_t width = ((uint32_t)data[16] << 24) |
                     ((uint32_t)data[17] << 16) |
                     ((uint32_t)data[18] << 8)  |
                     ((uint32_t)data[19]);

    uint32_t height = ((uint32_t)data[20] << 24) |
                      ((uint32_t)data[21] << 16) |
                      ((uint32_t)data[22] << 8)  |
                      ((uint32_t)data[23]);

    list[0] = (int)width;

    list[1] = (int)height;

    return list;
}

unsigned char *vq_png_parse(char *buf,size_t size)
{
    const unsigned char *data = (const unsigned char *)buf;

    // Used Variables
    int p = 8; // pointer in the file

    // buffer for decompression
    unsigned char *idat_buf = malloc(size);
    size_t idat_buf_len = 0;
    
    //Palette
    uint8_t *palette = NULL;
    size_t palette_len = 0;

    // Variables to safe
    uint32_t width;
    uint32_t height;
    int bit_depth;
    int color_type;

    vq_log("bytes: %02X\n", data[0]);
    vq_log("bytes: %02X\n", data[1]);
    vq_log("bytes: %02X\n", data[2]);
    vq_log("bytes: %02X\n", data[7]);
    vq_log("bytes: %02X\n", data[8]);

    while (p < (int)size) {

        uint32_t len = ((uint32_t)data[p] << 24)   |
                       ((uint32_t)data[p+1] << 16) |
                       ((uint32_t)data[p+2] << 8)  |
                       ((uint32_t)data[p+3]);

        char type[5];

        type[0] = (char)data[p+4];
        type[1] = (char)data[p+5];
        type[2] = (char)data[p+6];
        type[3] = (char)data[p+7];
        type[4] = '\0';

        vq_log("type: %s | len: %d\n",type,len);

        if (strcmp(type,"IHDR") == 0) {

            width =  ((uint32_t)data[p+8] << 24) |
                              ((uint32_t)data[p+9] << 16) |
                              ((uint32_t)data[p+10] << 8) |
                              ((uint32_t)data[p+11]);

            height = ((uint32_t)data[p+12] << 24) |
                              ((uint32_t)data[p+13] << 16) |
                              ((uint32_t)data[p+14] << 8)  |
                              ((uint32_t)data[p+15]);

            bit_depth = (int)data[p+16];
            color_type = (int)data[p+17];
            int compression_method = (int)data[p+18];
            int filter_method = (int)data[p+19];
            int interlace_method = (int)data[p+20];

            vq_log("Width:\t\t\t %d\n",width);
            vq_log("Height:\t\t\t %d\n",height);
            vq_log("Bit depth:\t\t %d\n",bit_depth);
            vq_log("Color type:\t\t %d\n",color_type);
            vq_log("Compression method:\t %d\n",compression_method);
            vq_log("Filter method:\t\t %d\n",filter_method);
            vq_log("Interlace method:\t %d\n",interlace_method);
        }

        // PLTE
        if (strcmp(type,"PLTE") == 0) {
            palette_len = len;
            palette = malloc(palette_len);

            memcpy(palette, data + p + 8, palette_len);
        }

        if (strcmp(type,"IDAT") == 0) {
            int compression_method = (int)data[p+8];
            int additional_flags = (int)data[p+9];

            memcpy(idat_buf + idat_buf_len, data + p + 8, len);
            idat_buf_len += len;
        } 

        p += 12 + len;

    }

    unsigned char *rgba = malloc(width * height * 4);

    vq_log("idat lenght: %d\n",idat_buf_len);

    // Type 2
    if (color_type == 2) {
        size_t row_bytes = (size_t)width * 3;
        size_t expected_size = height * (row_bytes + 1);

        uint8_t *raw = malloc(expected_size);
        uint8_t *pixels = malloc((size_t)width * height * 3);

        png_inflate(idat_buf, idat_buf_len, raw, expected_size);

        png_unfilter(raw, pixels, width, height, 3, row_bytes);

        for (size_t i = 0; i < (size_t)width * height; i++) {
            rgba[i * 4 + 0] = pixels[i * 3 + 0];
            rgba[i * 4 + 1] = pixels[i * 3 + 1];
            rgba[i * 4 + 2] = pixels[i * 3 + 2];
            rgba[i * 4 + 3] = 255;
        }

        free(raw);
        free(pixels);
    }

    // Type 3
    if (color_type == 3) {
        size_t row_bytes = ((size_t)width * bit_depth + 7) / 8;
        size_t expected_size = height * (row_bytes + 1);

        uint8_t *raw = malloc(expected_size);
        uint8_t *pixels = malloc(width * height);

        png_inflate(idat_buf, idat_buf_len, raw, expected_size);

        png_unfilter(raw, pixels, width, height, 1, row_bytes);

        for (uint32_t i = 0; i < width * height; i++) {
             uint8_t index = pixels[i];

             rgba[i * 4 + 0] = (unsigned char)palette[index * 3 + 0];
             rgba[i * 4 + 1] = (unsigned char)palette[index * 3 + 1];
             rgba[i * 4 + 2] = (unsigned char)palette[index * 3 + 2];
             rgba[i * 4 + 3] = 255;
        }

        free(raw);
        free(pixels);
    }

    // Type 6
    if (color_type == 6) {
        size_t row_bytes = (size_t)width * 4;
        size_t expected_size = height * (row_bytes + 1);

        uint8_t *raw = malloc(expected_size);

        png_inflate(idat_buf, idat_buf_len, raw, expected_size);

        png_unfilter(raw, rgba, width, height, 4, row_bytes);
    }

    return rgba;
}
