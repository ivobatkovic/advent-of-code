#include "year2022/day2/c/solutions.h"

#include <stdlib.h>
#include <string.h>

#include "utils/c_utils.h"

typedef struct string_array input_type;

static void free_input(input_type input) { free_string_array(input); }

static input_type transform_input(const char *const input_string) {
    (void)input_string;
    input_type transformed = {.size = 0, .data = NULL};
    return transformed;
}

static char *solve_part1(const char *const input_string) {
    input_type input = transform_input(input_string);

    char *output = malloc(20 * sizeof(char));
    strcpy(output, "Implement part one");

    free_input(input);
    return output;
}

static char *solve_part2(const char *const input_string) {
    input_type input = transform_input(input_string);

    char *output = malloc(20 * sizeof(char));
    strcpy(output, "Implement part one");

    free_input(input);
    return output;
}

const struct Year2022Day2 year2022day2 = {.solve_part1 = solve_part1,
                                          .solve_part2 = solve_part2};
