#ifndef _DAY4_H_
#define _DAY4_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <map>
#include <string>
#include <vector>

namespace day4 {

// Default input type for each day: need to change
using input_type = std::vector<std::map<std::string, std::string>>;

// Transformation method: parse input -> input_typ
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

std::string solve_part1(input_type input);

std::string solve_part2(input_type input);
}  // namespace day4

#endif
