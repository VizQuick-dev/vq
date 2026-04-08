#include <stdio.h>
#include "../parse/argv.h"
#include "../parse/filetype.h"

int main(int argc, char *argv[])
{
    char *input_filename = parse_argv_get_input_filename(argc,argv);
    char *output_filename = parse_argv_get_output_filename(argc,argv);
    char *input_filetype = parse_filetype_get(input_filename);
    char *output_filetype = parse_filetype_get(output_filename);

    printf("filetype (in): %s\n",input_filetype);
    printf("filetype (out): %s\n",output_filetype);
    return 0;
}