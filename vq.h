#ifndef VQ_H
#define VQ_H

#include <stdio.h>

#ifdef ENABLE_LOG
    #define vq_log(...) fprintf(stderr, __VA_ARGS__)
#else
    #define vq_log(...) ((void)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void vq_set_error(const char *error);
unsigned char *vq_parse(char *filename, int *width, int *height);

#ifdef __cplusplus
}
#endif

#endif
