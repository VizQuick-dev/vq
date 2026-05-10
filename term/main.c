#include <stdio.h>
#include "../parse/file.h"
#include "../parse/filetype.h"
#include "../parse/list.h"

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("usage: vqterm <file>\n");
        return 1;
    }else{
    char *input_filename = argv[1];
    int input_check = parse_check_file(input_filename);

    if(input_check == 1){
        char *input_filetype = parse_filetype_get(input_filename);

        parse_list_func_size func_size = parse_list_get_size(input_filetype);

        if(func_size != NULL)
        {
            char *input_filecontent = read_file(input_filename);
            int *result = func_size(input_filecontent);
            printf("x=%d; y=%d\n",result[0],result[1]);
        }
    }

    return 0;
    }
}
