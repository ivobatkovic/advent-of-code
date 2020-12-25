#ifndef _DAY23_H_
#define _DAY23_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <unordered_map>
#include <vector>
namespace day23 {

// Default input type for each day: need to change
using output_type = size_t;
using input_type = std::vector<int>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

std::unordered_map<int, int> play_game(const input_type &input,
                                       int n_rounds = 100,
                                       bool part_two = false);
output_type solve_part1(const input_type &input, int n_rounds = 10);

output_type solve_part2(const input_type &input, int n_rounds = 1e7);
}  // namespace day23

#endif
