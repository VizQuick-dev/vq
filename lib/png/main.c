#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int *vq_png_size(char *buf,size_t size)
{
    //todo
    int *list = malloc(2 * sizeof(int));

    if (sizeof(buf) < 24)
        return list;

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
    //todo
    printf("[PNG] decoding png\n");
    char *p = buf;

    if (*p != 'P' || *(p + 1) != '3')
        return NULL;
    p += 2;

    #define SKIP() \
        while (1) { \
            while (isspace((unsigned char)*p)) p++; \
            if (*p == '#') { \
                while (*p && *p != '\n') p++; \
            } else break; \
        }

    SKIP();
    int width = (int)strtol(p, &p, 10);

    SKIP();
    int height = (int)strtol(p, &p, 10);

    SKIP();
    int density = (int)strtol(p, &p, 10);

    printf("[ LOGS ]    density=%d\n",density);

    unsigned char *rgba = malloc(width * height * 4);
    if (!rgba)
        return NULL;

    for (int i = 0; i < width * height; i++) {
        SKIP();
        int r = (int)strtol(p, &p, 10);

        SKIP();
        int g = (int)strtol(p, &p, 10);

        SKIP();
        int b = (int)strtol(p, &p, 10);

        rgba[4 * i + 0] = (unsigned char)r;
        rgba[4 * i + 1] = (unsigned char)g;
        rgba[4 * i + 2] = (unsigned char)b;
        rgba[4 * i + 3] = 255;
    }
    return rgba;
}
