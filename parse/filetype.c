#include <string.h>
#include <stdio.h>

char *parse_filetype_get(unsigned char *bytes,size_t size)
{
    if (size < 2)
        return NULL;

    if (bytes[0] == 0x42 && bytes[1] == 0x4d)
        return "bmp";

    if (bytes[0] == 0xff && bytes[1] == 0xd8)
        return "jpeg";

    if (bytes[0] == 0x50 && (bytes[1] == 0x31 || bytes[1] == 0x34))
        return "pbm";

    if (bytes[0] == 0x50 && (bytes[1] == 0x32 || bytes[1] == 0x35))
        return "pgm";

    if (bytes[0] == 0x89 && bytes[1] == 0x50)
        return "png";

    if (bytes[0] == 0x50 && (bytes[1] == 0x33 || bytes[1] == 0x36))
        return "ppm";

    return NULL;
}

int parse_check_file(char *filename){
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }else{
        return 0;
    }
}
