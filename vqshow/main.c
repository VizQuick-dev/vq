#include <stdio.h>
#include "../parse/filetype.h"

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("usage: vqshow <file>\n");
	return 1;
    }else{
  	char *input_filename = argv[1];
	int input_check = parse_check_file(input_filename);
	
	printf("%d",input_check);

	return 0;
    }
}
