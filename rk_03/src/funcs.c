#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"

int open_read_file(FILE **f, const char *file_name)
{
    if (file_name == NULL)
        return ERR_FILE;

    *f = fopen(file_name, "r");

    if (*f == NULL)
        return ERR_FILE;

    fseek(*f, 0, SEEK_END);
    long pos = ftell(*f);

    if (pos <= 0)
        return ERR_EMPTY;

    fseek(*f, 0, SEEK_SET);

    return OK;
}

int open_write_file(FILE **f, const char *file_name)
{
    if (file_name == NULL)
        return ERR_FILE;

    *f = fopen(file_name, "w");

    if (*f == NULL)
        return ERR_FILE;

    return OK;
}

int file_size(FILE *f, int *f_size)
{
    char *elem = malloc(MAX_STR);
    *f_size = 0;

    long poz = ftell(f);

    while (fscanf(f, "%s", elem) == 1)
        (*f_size)++;

    if (!feof(f))
        return ERR_IO;

    fseek(f, poz, SEEK_SET);
    free(elem);

    return OK;
}

int scan_array(FILE *f, char ***arr, int **dups)
{
    char *elem1 = malloc(MAX_STR), *elem2 = malloc(MAX_STR);

    if (!elem1 || !elem2)
        return ERR_MEMORY;

    int tmp_size = 0;
    int found = 0;
    int dups_size = 0;
    long poz = ftell(f);

    while (fscanf(f, "%s", elem1) == 1)
    {
        (*dups)[dups_size]++;
        poz = ftell(f);
        while (fscanf(f, "%s", elem2) == 1)
        {
            if (strcmp(elem1, elem2) == 0)
            {
                found = 1;
                (*dups)[dups_size]++;
            }
        }
        dups_size++;

        if (found == 0)
        {
            (*arr) = realloc(*arr, (tmp_size + 1) * sizeof(char *));
            if (!(*arr))
            {
                free(elem1);
                free(elem2);
                return ERR_MEMORY;
            }
            (*arr)[tmp_size] = malloc(strlen(elem1) + 1);
            if (!(*arr)[tmp_size])
            {
                free(elem1);
                free(elem2);
                return ERR_MEMORY;
            }
            strcpy((*arr)[tmp_size], elem1);
            tmp_size++;
        }
        found = 0;
        fseek(f, poz, SEEK_SET);
    }

    free(elem1);
    free(elem2);

    if (!feof(f) && ferror(f))
    {
        for (int i = 0; i < tmp_size; i++)
            free((*arr)[i]);
            
        free(*arr);
        return ERR_IO;
    }

    return tmp_size;
}

void print_array(FILE *f, char **arr, int *dups, int size)
{
    for (int i = 0; i < size; i++)
        fprintf(f, "%s: %d\n", arr[i], dups[i]);
}

int string_cmp(const void *a, const void *b)
{
    const char **l = (const char **)a;
    const char **r = (const char **)b;

    return strcmp(*l, *r);
}
