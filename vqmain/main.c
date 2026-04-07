#include <stdio.h>
#include "../parse/argv.h"
#include "../parse/filetype.h"

int main(int argc, char *argv[])
{
    char *input_filename = parse_argv_get_input_filename(argc,argv);
    char *output_filename = parse_argv_get_output_filename(argc,argv);
//    char *data_string = parse_argv_get_data_string(argc,argv);

    printf("Input file: %s",input_filename);
    printf("Output file: %s",output_filename);
    return 0;
}