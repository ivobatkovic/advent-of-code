#include "solutions.h"
#include "c_utils.h"
#include "stdio.h"

struct input_struct {
    size_t n_elements;
    int * data;
}; 

char * day1_solve_part1(const char * const input) {
    struct string_array a = split_string(input, "\n"); 
    struct input_struct b;
    b.n_elements = a.n_strings;
    b.data = malloc(sizeof(*b.data) * b.n_elements);

    for (size_t i = 0; i < b.n_elements; ++i) {
        b.data[i] = atoi(a.strings[i]);
    }

    int c=0;
    for (size_t i = 0; i < b.n_elements; ++i) {
        c += (int)(b.data[i]/3.0)-2;
    }
    printf("Fuel needed %d\n",c);

    free_string_array(a);
    free(b.data);

    (void)input;
    return "ABCD";
}


char * day1_solve_part2(const char * const input) {
    (void)input;
    return "BCDE";
}

char * read_file(char* file_name) {
    return read_file_contents(file_name);
}

const struct day1 Day1 = {
    .read_file = read_file,
    .solve_part1 = day1_solve_part1,
    .solve_part2 = day1_solve_part2
};
