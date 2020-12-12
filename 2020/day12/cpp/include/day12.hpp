#ifndef _DAY12_H_
#define _DAY12_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <vector>

namespace day12 {

// Default input type for each day: need to change
using output_type = std::string;
using input_type = std::vector<std::string>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

output_type solve_part1(input_type input);

output_type solve_part2(input_type input);
}  // namespace day12

#endif
