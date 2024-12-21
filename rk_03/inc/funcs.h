#ifndef FUNCS__
#define FUNCS__

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_MEMORY 2
#define ERR_EMPTY 3
#define ERR_FILE 4

#define MAX_STR 50

int open_read_file(FILE **f, const char *file_name);
int open_write_file(FILE **f, const char *file_name);
int file_size(FILE *f, int *f_size);
int scan_array(FILE *f, char ***arr, int **dups);
void print_array(FILE *f, char **arr, int *dups, int size);
int string_cmp(const void *a, const void *b);

#endif