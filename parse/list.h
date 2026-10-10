#ifndef PARSE_LIST_H
#define PARSE_LIST_H
typedef int* (*parse_list_func_size) (char*,size_t);
parse_list_func_size parse_list_get_size(const char*);
typedef unsigned char* (*parse_list_func_parse) (char*,size_t);
parse_list_func_parse parse_list_get_parse(const char*);

#endif
