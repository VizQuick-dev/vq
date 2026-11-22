#ifndef LIB_JPEG_MAIN_H
#define LIB_JPEG_MAIN_H

#include <stddef.h>

int* vq_jpeg_size(unsigned char *buf,size_t size);
unsigned char* vq_jpeg_parse(unsigned char *buf,size_t size);

#endif
