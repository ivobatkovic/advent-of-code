#ifndef _2019_DAY1_C_H
#define _2019_DAY1_C_H

struct day1 {
    char* (*solve_part1)(const char * const);
    char* (*solve_part2)(const char * const);
    char* (*read_file)(char*);
};

extern const struct day1 Day1;

#endif
