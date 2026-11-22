#ifndef LIB_BMP_MAIN_H
#define LIB_BMP_MAIN_H

#include <stddef.h>

int* vq_bmp_size(unsigned char *buf,size_t size);
unsigned char* vq_bmp_parse(unsigned char *buf,size_t size);

#endif
