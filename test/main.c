#include <stdio.h>
#include <stdint.h>

#include "../vq.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: vqtest <file>\n");
        return 1;
    }

    char *input_filename = argv[1];
    int width,height;
    
    uint8_t *pixels = vq_parse(input_filename,&width,&height);

    if(pixels == NULL) {
        fprintf(stderr, "VQ Error: %s\n", vq_get_error());
    }

    return 0;
}
