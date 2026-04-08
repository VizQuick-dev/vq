#include <string.h>

#include <stdio.h>

char *parse_filetype_get(char *filename)
{
    char * ptr;
    int ch = '.';
    ptr = strchr( filename, ch );
    return ptr;
}