#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int *vq_ppm_size(char *buf)
{
    int *list = malloc(2 * sizeof(int));
    if (list == NULL)
        return NULL;

    char *p = buf;

    if (*p != 'P') {
        free(list);
        return NULL;
    }
    p += 2;

    while (1) {
        while (isspace((unsigned char)*p))
            p++;

        if (*p == '#') {
            while (*p != '\n' && *p != '\0')
                p++;
            continue;
        }

        break;
    }

    list[0] = (int)strtol(p, &p, 10);

    while (1) {
        while (isspace((unsigned char)*p))
            p++;

        if (*p == '#') {
            while (*p != '\n' && *p != '\0')
                p++;
            continue;
        }

        break;
    }

    list[1] = (int)strtol(p, &p, 10);

    return list;
}

unsigned char *vq_ppm_parse(char *buf)
{
    printf("[PPM] decoding ppm\n");
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
