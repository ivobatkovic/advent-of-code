#include "include/solutions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char * input = Day1.read_file("2019/day1/data/input.txt");

    printf("Interface %s\n",Day1.solve_part1(input));
    printf("Interface %s\n",Day1.solve_part2(input));

    free(input);
    return 0;
}
