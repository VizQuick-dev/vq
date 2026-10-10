#ifndef VQ_H
#define VQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include <vq/parse/file.h>
#include <vq/parse/filetype.h>
#include <vq/parse/list.h>

unsigned char *vq_parse(char *filename, int *width, int *height) {
    char *filetype = parse_filetype_get(filename);

    printf("%s\n",filetype);

    if (filetype != NULL) {
        char *input_filecontent = read_file(filename);
        parse_list_func_size vq_func_size = parse_list_get_size(filetype);
        parse_list_func_parse vq_func_parse = parse_list_get_parse(filetype);

        int *size = vq_func_size(input_filecontent);

        printf("%s\n",filename);
        printf("%d,%d\n",size[0],size[1]);

        *width = size[0];
        *height = size[1];

        free(size);

        return vq_func_parse(input_filecontent);
    }

    return NULL;
}

#ifdef __cplusplus
}
#endif

#endif
