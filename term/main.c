#include <stdio.h>
#include <locale.h>

#include "../parse/file.h"
#include "../parse/filetype.h"
#include "../parse/list.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    const char *block = "▄";

    if (argc < 2) {
        printf("usage: vqterm <file>\n");
        return 1;
    }

    printf("hi <3\n");

    char *input_filename = argv[1];

    if (parse_check_file(input_filename) != 1) {
        printf("invalid file\n");
        return 1;
    }

    char *input_filetype = parse_filetype_get(input_filename);

    printf("[ LOGS ]    filetype=%s\n", input_filetype);

    if (input_filetype == NULL) {
        printf("input_filetype NULL\n");
        return 1;
    }

    parse_list_func_size func_size = parse_list_get_size(input_filetype);
    parse_list_func_parse func_parse = parse_list_get_parse(input_filetype);

    if (func_size == NULL || func_parse == NULL) {
        printf("unsupported filetype\n");
        return 1;
    }

    char *input_filecontent = read_file(input_filename);

    int *result_size = func_size(input_filecontent);
    unsigned char *result = func_parse(input_filecontent);

    if(result_size == NULL) {
         printf("result_size NULL\n");
    }

    for (int y = 0; y < result_size[1]; y += 2)
    {
        for (int x = 0; x < result_size[0]; x++)
        {
            int top = (y * result_size[0] + x) * 4;

            int bottom;
            if (y + 1 < result_size[1])
                bottom = ((y + 1) * result_size[0] + x) * 4;
            else
                bottom = top;

            printf("\033[38;2;%d;%d;%dm",
                   result[bottom + 0],
                   result[bottom + 1],
                   result[bottom + 2]);

            printf("\033[48;2;%d;%d;%dm",
                   result[top + 0],
                   result[top + 1],
                   result[top + 2]);

            fputs(block, stdout);
        }

        printf("\033[0m\n");
    }

    return 0;
}
