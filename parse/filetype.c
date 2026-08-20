#include <string.h>
#include <stdio.h>

char *parse_filetype_get(char *filename)
{
    FILE *file;
    unsigned char bytes[2];

    file = fopen(filename, "rb");
    if (fread(bytes, 1, sizeof(bytes), file) < 2) {
       fclose(file);
       return NULL;
    }

    fclose(file);

    if (bytes[0] == 0x50 && bytes[1] == 0x31)
        return "pbm";

    if (bytes[0] == 0x50 && bytes[1] == 0x34)
        return "pbm";

    if (bytes[0] == 0x50 && bytes[1] == 0x33)
        return "ppm";

    if (bytes[0] == 0x50 && bytes[1] == 0x36)
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
