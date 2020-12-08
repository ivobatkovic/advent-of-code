#ifndef _DAY8_H_
#define _DAY8_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <unordered_set>
#include <vector>

namespace day8 {

// Default input type for each day: need to change
using input_type = std::string;

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

std::string solve_part1(input_type input);

std::string solve_part2(input_type input);
}  // namespace day8

#endif
