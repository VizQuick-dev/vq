#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

char *parse_argv_get_input_filename(int argc,char *argv[])
{
    int i;
    bool last_was_correct_parameter = false;
    char *input_filename;

    for (i = 1; i < argc; i++) {
        if (last_was_correct_parameter) {
            input_filename = argv[i];
        }
        last_was_correct_parameter = strcmp(argv[i], "-i") == 0;
    }
    return input_filename;
}

char *parse_argv_get_output_filename(int argc,char *argv[])
{
    int i;
    int k = 0;
    char *output_filename;

    for (i = 1; i < argc; i++) {
        if (k == 0) {
            if (argv[i][0] == '-') {
                k = 1;
            } else {
                output_filename = argv[i];
            }
        } else {
            k = 0;
        }
    }
    return output_filename;
}