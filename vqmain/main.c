#include <stdio.h>
#include "../parse/argv.h"
#include "../parse/filetype.h"

int main(int argc, char *argv[])
{
    char *input_filename = parse_argv_get_input_filename(argc,argv);
    char *output_filename = parse_argv_get_output_filename(argc,argv);
    char *input_filetype = parse_filetype_get(input_filename);
    char *output_filetype = parse_filetype_get(output_filename);
    int input_check = parse_check_file(input_filename);
    int output_check = parse_check_file(output_filename);

    printf("check (in): %d\n",input_check);
    printf("check (out): %d\n",output_check);
    return 0;
}