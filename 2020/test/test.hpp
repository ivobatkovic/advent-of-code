#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include <vector>

// Input type i'm going to parse into for each day
// After bootstrapping, this needs to be modified
using input_type = std::vector<std::string>;

std::string solve_part1(input_type input);
std::string solve_part2(input_type input);

#endif // _TEST_H
