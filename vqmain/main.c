#include <stdio.h>
#include "../parse/argv.h"
#include "../parse/filetype.h"
#include "../parse/list.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("please read the docs in /docs/vq.html\n");
        return 1;
    }
    else
    {
        char *input_filename = parse_argv_get_input_filename(argc,argv);
        char *output_filename = parse_argv_get_output_filename(argc,argv);
        char *input_filetype = parse_filetype_get(input_filename);
        char *output_filetype = parse_filetype_get(output_filename);
        int input_check = parse_check_file(input_filename);

        parse_list_func_size func_size = parse_list_get_size(input_filetype);

        if(func_size != NULL)
        {
            int *result = func_size("test");
            printf("x=%d; y=%d\n",result[0],result[1]);
        }

        return 0;
    }
}