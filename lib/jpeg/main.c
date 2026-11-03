#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "vq.h"

int* vq_jpeg_size(char *buf,size_t size)
{
    int *list = malloc(2 * sizeof(int));

    vq_log("hi! %zu \n",size);

    int width = 0;
    int height = 0;
    long int p = 2;

    while (p + 4 <= size)
    {
        uint16_t marker = ((uint16_t)(uint8_t)buf[p] << 8) | (uint8_t)buf[p + 1];

        uint16_t length = ((uint16_t)(uint8_t)buf[p + 2] << 8) | (uint8_t)buf[p + 3];

        vq_log("ID: %02x%02x, Seg: %u\n",
           (uint8_t)buf[p],
           (uint8_t)buf[p + 1],
           length);

        if (length < 2 || (size_t)length > size - p - 2)
            break;

        if (marker == 0xFFC0) {

            height =(int)((uint16_t)(uint8_t)buf[p + 5] << 8) | (uint8_t)buf[p + 6];

            width = (int)((uint16_t)(uint8_t)buf[p + 7] << 8) | (uint8_t)buf[p + 8];

            vq_log("size: %ux%u\n",width,height);

            break;
        }

        p += 2 + length;
    }

    list[0] = width;

    list[1] = height;

    return list;
}

unsigned char* vq_jpeg_parse(char *buf,size_t size){
    char *pixels;

    long int p = 2;

    while (p + 4 <= size)
    {
        uint16_t marker = ((uint16_t)(uint8_t)buf[p] << 8) | (uint8_t)buf[p + 1];

        uint16_t length = ((uint16_t)(uint8_t)buf[p + 2] << 8) | (uint8_t)buf[p + 3];

        vq_log("ID: %02x%02x, Seg: %u\n",
           (uint8_t)buf[p],
           (uint8_t)buf[p + 1],
           length);

        if (length < 2 || (size_t)length > size - p - 2)
            break;

        if (marker == 0xFFC0) {

            int height =(int)((uint16_t)(uint8_t)buf[p + 5] << 8) | (uint8_t)buf[p + 6];

            int width = (int)((uint16_t)(uint8_t)buf[p + 7] << 8) | (uint8_t)buf[p + 8];

            pixels = malloc(width * height * 4);

        }

        p += 2 + length;
    }

    return pixels;
}