#ifndef _DAY20_H_
#define _DAY20_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <unordered_map>
#include <vector>

namespace day20 {

// Default input type for each day: need to change
using output_type = int64_t;
using input_type = std::unordered_map<std::string, std::vector<std::string>>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

output_type solve_part1(const input_type &input);

output_type solve_part2(const input_type &input);
}  // namespace day20

#endif
