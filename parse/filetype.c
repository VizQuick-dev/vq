#include <string.h>
#include <stdio.h>

char *parse_filetype_get(char *filename)
{
    char * ptr;
    int ch = '.';
    ptr = strchr( filename, ch );
    return ptr;
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