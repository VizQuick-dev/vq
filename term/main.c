#include <stdio.h>
#include <locale.h>
#include <stdint.h>

#include "../vq.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    const char *block = "▄";

    if (argc < 2) {
        printf("usage: vqterm <file>\n");
        return 1;
    }

    char *input_filename = argv[1];
    int width,height;
    
    uint8_t *pixels = vq_parse(input_filename,&width,&height);

    if(pixels == NULL) {
        fprintf(stderr, "VQ Error: %s\n", vq_get_error());
    }

    for (int y = 0; y < height; y += 2)
    {
        for (int x = 0; x < width; x++)
        {
            int top = (y * width + x) * 4;

            int bottom;
            if (y + 1 < height)
                bottom = ((y + 1) * width + x) * 4;
            else
                bottom = top;

            printf("\033[38;2;%d;%d;%dm",
                   pixels[bottom + 0],
                   pixels[bottom + 1],
                   pixels[bottom + 2]);

            printf("\033[48;2;%d;%d;%dm",
                   pixels[top + 0],
                   pixels[top + 1],
                   pixels[top + 2]);

            fputs(block, stdout);
        }

        printf("\033[0m\n");
    }

    return 0;
}
