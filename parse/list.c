#include <stdio.h>
#include <string.h>

#include "../lib/bmp/main.h"
#include "../lib/jpeg/main.h"
#include "../lib/pbm/main.h"
#include "../lib/pgm/main.h"
#include "../lib/ppm/main.h"
#include "../lib/png/main.h"

typedef int* (*parse_list_func_size) (unsigned char*,size_t);
typedef unsigned char* (*parse_list_func_parse) (unsigned char*,size_t);

typedef struct
{
    const char *ext;
    parse_list_func_size fns;
    parse_list_func_parse fnp;
} item;

item list[] = {
    {"bmp", vq_bmp_size, vq_bmp_parse},
    {"jpeg", vq_jpeg_size, vq_jpeg_parse},
    {"pbm", vq_pbm_size, vq_pbm_parse},
    {"pgm", vq_pgm_size, vq_pgm_parse},
    {"ppm", vq_ppm_size, vq_ppm_parse},
    {"png", vq_png_size, vq_png_parse},
};

size_t list_size = sizeof(list) / sizeof(list[0]);

parse_list_func_size parse_list_get_size(const char *searchparam) {
    for (size_t i = 0; i < list_size; i++) {
        if (strcmp(list[i].ext, searchparam) == 0) {
            return list[i].fns;
        }
    }
    return NULL;
}

parse_list_func_parse parse_list_get_parse(const char *searchparam) {
    for (size_t i = 0; i < list_size; i++) {
        if (strcmp(list[i].ext, searchparam) == 0) {
            return list[i].fnp;
        }
    }
    return NULL;
}
