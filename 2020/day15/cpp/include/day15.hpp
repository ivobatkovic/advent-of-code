#ifndef _DAY15_H_
#define _DAY15_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <vector>

namespace day15 {

// Default input type for each day: need to change
using output_type = int;
using input_type = std::vector<int>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

output_type solve_part1(const input_type &input, int nth_digit = 2020);

output_type solve_part2(const input_type &input);
}  // namespace day15

#endif
