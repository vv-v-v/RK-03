#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"

int main(void)
{
    FILE *in, *out;
    char **unic_chars = NULL;
    int rc;

    rc = open_read_file(&in, "in.txt");
    if (rc != OK)
        return rc;

    int file_count;
    file_size(in, &file_count);

    unic_chars = malloc(file_count * sizeof(char *));
    if (unic_chars == NULL)
        return ERR_MEMORY;

    rewind(in);
    int *dups = malloc(sizeof(int) * file_count);
    if (!dups)
        return ERR_MEMORY;

    rc = scan_array(in, &unic_chars, &dups);
    if (rc < 0)
    {
        free(unic_chars);
        return ERR_IO;
    }
    fclose(in);
    int new_size = rc;
    char **chars_new = realloc(unic_chars, rc * sizeof(char *));
    if (!chars_new)
        return ERR_MEMORY;
    
    chars_new = unic_chars;
    rc = open_write_file(&out, "out.txt");
    if (rc != OK)
    {
        free(chars_new);
        return rc;
    }

    qsort(chars_new, new_size, sizeof(char *), string_cmp);
    print_array(out, chars_new, dups, new_size);
    fclose(out);
    free(chars_new);
    free(dups);

    return OK;
}
