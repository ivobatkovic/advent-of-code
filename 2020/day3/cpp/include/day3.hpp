#ifndef _DAY3_H_
#define _DAY3_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <vector>

namespace day3 {

// Default input type for each day: need to change
using input_type = std::vector<std::string>;

// Transformation method: parse input -> input_typ
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

std::string solve_part1(const input_type &input);

std::string solve_part2(const input_type &input);
}  // namespace day3

#endif
