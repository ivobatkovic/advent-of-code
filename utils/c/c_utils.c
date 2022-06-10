#include "include/c_utils.h"

#include <stdio.h>
#include <string.h>

void free_string_array(struct string_array array) {
    for (size_t i = 0; i < array.n_strings; ++i) {
        if (array.strings[i]) {
            free(array.strings[i]);
        }
    }
    if (array.strings) {
        free(array.strings);
    }
}

struct string_array split_string(const char * const string, const char *delim) {

    struct string_array a;
    a.n_strings = 4;
    a.strings = malloc((a.n_strings) * sizeof(char *));
    if (!a.strings) {
        fprintf(stderr,"Failed memory allocation in split_string:40\n");
        exit(1);
    }

    char *string_copy = malloc( (strlen(string)+1) * sizeof(char));
    if (!string_copy) {
        fprintf(stderr, "Failed memory allocation in split_string:46\n");
        exit(1);
    }
    strcpy(string_copy,string);
    
    char* token = strtok(string_copy, delim);
    size_t count = 0;
    while ( token != NULL) {
        if (count > a.n_strings - 1) {
            a.n_strings *= 2;
            char ** reallocated_strings = realloc(a.strings, a.n_strings * sizeof(char *));
            if (!reallocated_strings) {
                fprintf(stderr, "Failed reallocation in split_string:58\n");
                exit(1);
            }
            a.strings = reallocated_strings;
        }

        a.strings[count] = malloc( (strlen(token)+1) * sizeof(char));
        if (!a.strings[count]) {
            fprintf(stderr, "Failed malloc in split_string:66\n");
            exit(1);
        }
        strcpy(a.strings[count],token);
        token = strtok(NULL, delim);
        count++;
    }

    a.n_strings = count;
    a.strings = realloc(a.strings, a.n_strings * sizeof(char *));

    free(string_copy);
    return a;
}


char *read_file_contents(char * file_name) {

    FILE *f = fopen(file_name,"r");
    if (!f) {
        fprintf(stderr, "Couldn't read file %s:86\n",file_name);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);

    fseek(f,0,SEEK_SET);
    char *buffer = malloc(length+1);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for file contents:95\n");
        exit(1);
    }
    
    if (fread(buffer,sizeof(*buffer),length,f) < length){
        fprintf(stderr, "Failed to read the input file to buffer:100\n");
    }
    buffer[length] = '\0';
    fclose(f);
    return buffer;
}
