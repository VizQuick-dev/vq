#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int* vq_bmp_size(unsigned char *buf,size_t size)
{
    int *list = malloc(2 * sizeof(int));

    if (size < 25)
        return NULL;

    const unsigned char *data = (const unsigned char *)buf;

    uint32_t width = ((uint32_t)data[18])       |
                     ((uint32_t)data[19] << 8)  |
                     ((uint32_t)data[20] << 16) |
                     ((uint32_t)data[21] << 24);

    uint32_t height = ((uint32_t)data[22])       |
                      ((uint32_t)data[23] << 8)  |
                      ((uint32_t)data[24] << 16) |
                      ((uint32_t)data[25] << 24);

    list[0] = (int)width;

    list[1] = (int)height;

    return list;
}

unsigned char* vq_bmp_parse(unsigned char *buf,size_t size)
{
    return NULL;
}