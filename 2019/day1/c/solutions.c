#include "solutions.h"

#include <stdlib.h>
#include <string.h>

#include "c_utils.h"
typedef struct string_array input_type;

input_type transform_input(const char *const input_string) {
    (void)input_string;
    input_type transformed = {.n_strings = 0, .strings = NULL};
    return transformed;
}

char *solve_part1(const char *const input_string) {
    input_type input = transform_input(input_string);
    (void)input;

    char *output = malloc(20 * sizeof(char));
    strcpy(output, "Implement part one");
    return output;
}

char *solve_part2(const char *const input_string) {
    input_type input = transform_input(input_string);
    (void)input;

    char *output = malloc(20 * sizeof(char));
    strcpy(output, "Implement part one");
    return output;
}

const struct day1 Day1 = {.solve_part1 = solve_part1,
                          .solve_part2 = solve_part2};
