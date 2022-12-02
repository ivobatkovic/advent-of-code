#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils/c_utils.h"
#include "year2022/day2/c/solutions.h"

int main(int argc, char** argv) {
    const char* file_name =
        (argc > 1) ? argv[1] : "year2022/day2/data/input.txt";
    char* input = read_file_contents(file_name);

    clock_t time = clock();
    char* part_one = year2022day2.solve_part1(input);
    time = clock() - time;
    double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
    printf("Solution to part one: %s (time taken %.2f [ms])\n", part_one,
           time_taken);

    time = clock();
    char* part_two = year2022day2.solve_part2(input);
    time = clock() - time;
    time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
    printf("Solution to part two: %s (time taken %.2f [ms])\n", part_two,
           time_taken);

    free(part_one);
    free(part_two);
    free(input);
    return 0;
}