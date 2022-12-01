#ifndef _C_UTILS_H
#define _C_UTILS_H

#include <stdlib.h>

/// Data type to hold an array of strings
///
/// @param n_strings Number of strings that the array holds
/// @param strings Pointer to the strings
struct string_array {
    size_t size;
    char **data;
};

/// Free the allocated contents of the string_array struct
///
/// @param array Object to be freed
void free_string_array(struct string_array array);

/// Split a string into a string_array struct
///
/// @param string Input string to be splut
/// @param delim Delimiter to split the string with
/// @return Struct containing the split strings
struct string_array split_string(const char *const string, const char *delim);

/// Read the entire file contents into a string
///
/// @param string File name
/// @return String containing the file contents
char *read_file_contents(const char *const file_name);

#endif
