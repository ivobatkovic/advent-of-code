#ifndef _2019_DAY1_C_H
#define _2019_DAY1_C_H

struct day1 {
    char* (*read_file)(char*);
    char* (*solve_part1)(char*);
    char* (*solve_part2)(char*);
};

extern const struct day1 Day1;

#endif
