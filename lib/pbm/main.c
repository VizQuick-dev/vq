#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int *vq_pbm_size(char *buf)
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

unsigned char *vq_pbm_parse(char *buf)
{
    char *p = buf;

    if (*p != 'P' || *(p + 1) != '1')
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

    unsigned char *rgba = malloc(width * height * 4);
    if (!rgba)
        return NULL;

    for (int i = 0; i < width * height; i++) {
        SKIP();

        int pixel = (int)strtol(p, &p, 10);

        unsigned char c = pixel ? 0 : 255;

        rgba[4 * i + 0] = c;
        rgba[4 * i + 1] = c;
        rgba[4 * i + 2] = c;
        rgba[4 * i + 3] = 255;
    }

    return rgba;
}