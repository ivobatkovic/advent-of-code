#include "utils/c_utils.h"

#include <stdio.h>
#include <string.h>

void free_string_array(struct string_array array) {
    for (size_t i = 0; i < array.size; ++i) {
        if (array.data[i]) {
            free(array.data[i]);
        }
    }
    if (array.data) {
        free(array.data);
    }
}

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

struct string_array split_string(const char *const string, const char *delim) {
    struct string_array output;
    output.size = 4;
    output.data = malloc((output.size) * sizeof(char *));
    if (!output.data) {
        fprintf(stderr, "Failed memory allocation in split_string:20\n");
        exit(1);
    }

    char *string_copy = malloc((strlen(string) + 1) * sizeof(char));
    if (!string_copy) {
        fprintf(stderr, "Failed memory allocation in split_string:28\n");
        exit(1);
    }
    strcpy(string_copy, string);

    char *token = strsep(&string_copy, delim);
    size_t count = 0;
    while (token != NULL) {
        if (count > output.size - 1) {
            output.size *= 2;
            char **reallocated_strings =
                realloc(output.data, output.size * sizeof(char *));
            if (!reallocated_strings) {
                fprintf(stderr, "Failed reallocation in split_string:41\n");
                exit(1);
            }
            output.data = reallocated_strings;
        }

        output.data[count] = malloc((strlen(token) + 1) * sizeof(char));
        if (!output.data[count]) {
            fprintf(stderr, "Failed malloc in split_string:49\n");
            exit(1);
        }
        strcpy(output.data[count], token);
        token = strsep(&string_copy, delim);
        count++;
    }

    output.size = count;
    output.data = realloc(output.data, output.size * sizeof(char *));

    free(string_copy);
    return output;
}

char *read_file_contents(const char *const file_name) {
    FILE *f = fopen(file_name, "r");
    if (!f) {
        fprintf(stderr, "Couldn't read file %s:67\n", file_name);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long int file_stream = ftell(f) - 1;
    size_t length = (file_stream < 0) ? 0U : (size_t)file_stream;

    fseek(f, 0, SEEK_SET);
    char *buffer = malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for file contents:82\n");
        exit(1);
    }

    if (fread(buffer, sizeof(*buffer), length, f) < length) {
        fprintf(stderr, "Failed to read the input file to buffer:87\n");
    }
    buffer[length] = '\0';
    fclose(f);
    return buffer;
}
