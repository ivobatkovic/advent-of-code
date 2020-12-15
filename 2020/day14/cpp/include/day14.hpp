#ifndef _DAY14_H_
#define _DAY14_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <tuple>
#include <vector>
namespace day14 {

// Default input type for each day: need to change
using output_type = int64_t;
using input_type = std::vector<std::tuple<std::string, std::vector<int>>>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

output_type solve_part1(const input_type &input);

output_type solve_part2(const input_type &input);
}  // namespace day14

#endif
