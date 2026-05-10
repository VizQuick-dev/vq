#include <stdlib.h>
#include <stdio.h>

int *vq_pbm_size(char *buf)
{
    int* list = malloc(2 * sizeof(int));
    list[0] = 1;
    list[1] = 1;
    return list;
}

int *vq_pbm_parse(char *buf)
{
    int* list = malloc(2 * sizeof(int));
    list[0] = 1;
    list[1] = 2;
    return list;
}