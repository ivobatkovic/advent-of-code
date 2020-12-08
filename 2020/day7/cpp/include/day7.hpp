#ifndef _DAY7_H_
#define _DAY7_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <unordered_map>
#include <vector>

namespace day7 {

// Default input type for each day: need to change
using bag_contents = std::pair<std::string, int>;
using input_type = std::unordered_map<std::string, std::vector<bag_contents>>;

// Transformation method: parse input -> input_typ
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

bool contains_bag(input_type &input_, std::string color);
std::string solve_part1(input_type input);

int bags_in_bag(input_type &bag, std::string color, int n_bags);
std::string solve_part2(input_type input);
}  // namespace day7

#endif
