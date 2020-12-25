#ifndef _DAY19_H_
#define _DAY19_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <unordered_map>
#include <vector>

namespace day19 {

// Default input type for each day: need to change
using message_type = std::vector<std::string>;
using rule_type = std::unordered_map<std::string, std::vector<message_type>>;
using output_type = int;
using input_type = std::tuple<rule_type, message_type>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

bool rule_check(rule_type &rules, const std::string &msg,
                message_type rule_nums);

output_type solve_part1(const input_type &input);

output_type solve_part2(const input_type &input);
}  // namespace day19

#endif
