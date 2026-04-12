#ifndef PARSE_LIST_H
#define PARSE_LIST_H
typedef int* (*parse_list_func_size) (char*);
parse_list_func_size parse_list_get_size(const char*);

#endif