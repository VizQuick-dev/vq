#ifndef LIB_PNG_MAIN_H
#define LIB_PNG_MAIN_H

#include <stddef.h>

int* vq_png_size(unsigned char*,size_t size);
unsigned char* vq_png_parse(unsigned char*,size_t size);

#endif
