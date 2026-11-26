
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "vq.h"

typedef struct {
    const unsigned char *buf;
    size_t size;
    size_t pos;
} ppm_reader;

static int ppm_skip(ppm_reader *r)
{
    while (r->pos < r->size) {
        unsigned char c = r->buf[r->pos];

        if (isspace(c)) {
            r->pos++;
            continue;
        }

        if (c == '#') {
            while (r->pos < r->size &&
                   r->buf[r->pos] != '\n')
                r->pos++;

            continue;
        }

        break;
    }

    return r->pos < r->size;
}

static int ppm_number(ppm_reader *r, int *out)
{
    if (!ppm_skip(r))
        return 0;

    size_t start = r->pos;

    while (r->pos < r->size &&
           isdigit(r->buf[r->pos]))
        r->pos++;

    if (start == r->pos)
        return 0;

    char tmp[32];
    size_t len = r->pos - start;

    if (len >= sizeof(tmp))
        return 0;

    memcpy(tmp, r->buf + start, len);
    tmp[len] = '\0';

    char *end;
    long value = strtol(tmp, &end, 10);

    if (*end || value < 0 || value > INT_MAX)
        return 0;

    *out = (int)value;
    return 1;
}

int *vq_ppm_size(unsigned char *buf, size_t size)
{
    if (!buf || size < 3)
        return NULL;

    ppm_reader r = { buf, size, 0 };

    if (r.buf[r.pos++] != 'P')
        return NULL;

    unsigned char type = r.buf[r.pos++];

    if (type != '3' && type != '6')
        return NULL;

    int *result = malloc(2 * sizeof(int));
    if (!result)
        return NULL;

    int maxval;

    if (!ppm_number(&r, &result[0]) ||
        !ppm_number(&r, &result[1]) ||
        !ppm_number(&r, &maxval) ||
        result[0] <= 0 ||
        result[1] <= 0 ||
        maxval <= 0 ||
        maxval > 65535) {
        free(result);
        return NULL;
    }

    return result;
}

unsigned char *vq_ppm_parse(unsigned char *buf, size_t size)
{
    if (!buf || size < 3)
        return NULL;

    vq_log("[PPM] decoding ppm\n");

    ppm_reader r = { buf, size, 0 };

    if (r.buf[r.pos++] != 'P')
        return NULL;

    unsigned char type = r.buf[r.pos++];

    if (type != '3' && type != '6')
        return NULL;

    int width, height, maxval;

    if (!ppm_number(&r, &width) ||
        !ppm_number(&r, &height) ||
        !ppm_number(&r, &maxval))
        return NULL;

    if (width <= 0 || height <= 0 ||
        maxval <= 0 || maxval > 65535)
        return NULL;

    vq_log("[ LOGS ] density=%d\n", maxval);

    size_t pixels = (size_t)width * (size_t)height;

    if (pixels > SIZE_MAX / 4)
        return NULL;

    unsigned char *rgba = malloc(pixels * 4);

    if (!rgba)
        return NULL;

    if (type == '3') {
        // ASCII PPM

        for (size_t i = 0; i < pixels; i++) {
            int red, green, blue;

            if (!ppm_number(&r, &red) ||
                !ppm_number(&r, &green) ||
                !ppm_number(&r, &blue)) {
                free(rgba);
                return NULL;
            }

            if (red > maxval || green > maxval || blue > maxval) {
                free(rgba);
                return NULL;
            }

            rgba[i * 4 + 0] = (unsigned char)((red * 255LL) / maxval);
            rgba[i * 4 + 1] = (unsigned char)((green * 255LL) / maxval);
            rgba[i * 4 + 2] = (unsigned char)((blue * 255LL) / maxval);
            rgba[i * 4 + 3] = 255;
        }
    } else {
        // Binary PPM

        // Consume the mandatory whitespace after maxval.
        if (r.pos >= r.size || !isspace(r.buf[r.pos])) {
            free(rgba);
            return NULL;
        }

        unsigned char separator = r.buf[r.pos++];

        // CRLF is a single line ending.
        if (separator == '\r' &&
            r.pos < r.size &&
            r.buf[r.pos] == '\n')
            r.pos++;

        int bytes_per_sample = maxval > 255 ? 2 : 1;

        if (pixels > (SIZE_MAX - r.pos) / (3 * bytes_per_sample) ||
            r.pos + pixels * 3 * bytes_per_sample > r.size) {
            free(rgba);
            return NULL;
        }

        for (size_t i = 0; i < pixels; i++) {
            for (int c = 0; c < 3; c++) {
                unsigned int value;

                if (bytes_per_sample == 1) {
                    value = r.buf[r.pos++];
                } else {
                    // P6 16-bit samples are big-endian.
                    value = ((unsigned int)r.buf[r.pos] << 8) |
                            r.buf[r.pos + 1];
                    r.pos += 2;
                }

                if (value > (unsigned int)maxval) {
                    free(rgba);
                    return NULL;
                }

                rgba[i * 4 + c] =
                    (unsigned char)((value * 255ULL) / maxval);
            }

            rgba[i * 4 + 3] = 255;
        }
    }

    return rgba;
}
