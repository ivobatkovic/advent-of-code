#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "solutions.h"

int main() {
    char* input = Day1.read_file("2019/day1/data/input.txt");

    clock_t time = clock();
    char* part_one = Day1.solve_part1(input);
    time = clock() - time;
    double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
    printf("Solution to part one: %s (time taken %.2f [ms])\n", part_one,
           time_taken);

    time = clock();
    char* part_two = Day1.solve_part2(input);
    time = clock() - time;
    time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
    printf("Solution to part two: %s (time taken %.2f [ms])\n", part_two,
           time_taken);

    free(part_one);
    free(part_two);
    free(input);
    return 0;
}
