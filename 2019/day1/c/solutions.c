#include "solutions.h"

#include "c_utils.h"
#include "stdio.h"

char *day1_solve_part1(const char *const input) {
    struct string_array a = split_string(input, "\n");

    int fuel_needed = 0;
    for (size_t i = 0; i < a.n_strings; ++i) {
        fuel_needed += (int)(atoi(a.strings[i]) / 3.0) - 2;
    }
    free_string_array(a);

    const int string_size = snprintf(NULL, 0, "%d", fuel_needed);
    char *output = malloc(string_size + 1);
    sprintf(output, "%d", fuel_needed);
    return output;
}

int compute_fuel(int mass) {
    int fuel = (int)(mass / 3.0) - 2;
    return (fuel > 0) ? fuel + compute_fuel(fuel) : 0;
}

char *day1_solve_part2(const char *const input) {
    struct string_array a = split_string(input, "\n");

    int fuel_needed = 0;
    for (size_t i = 0; i < a.n_strings; ++i) {
        fuel_needed += compute_fuel(atoi(a.strings[i]));
    }
    free_string_array(a);

    const int string_size = snprintf(NULL, 0, "%d", fuel_needed);
    char *output = malloc(string_size + 1);
    sprintf(output, "%d", fuel_needed);
    return output;
}

char *read_file(const char *const file_name) {
    return read_file_contents(file_name);
}

const struct day1 Day1 = {.read_file = read_file,
                          .solve_part1 = day1_solve_part1,
                          .solve_part2 = day1_solve_part2};
