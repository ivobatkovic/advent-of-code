#include "2020/day15/cpp/include/day15.hpp"

#include <unordered_map>

#include "utils/cpp/include/utils.hpp"

using day15::input_type;
using day15::output_type;

input_type day15::transform_input(std::vector<std::string> &input) {
  input_type output;
  std::vector<std::string> split;
  utils::split_string(input[0], ",", split);
  for (auto &inp : split) {
    output.push_back(std::stoi(inp));
  }
  return output;
}

input_type day15::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day15::solve_part1(const input_type &input_, int nth_digit) {
  // Pre-initialize a vector of size nth_digit
  std::vector<int> dig_spoken(nth_digit, 0);

  // To use less memory, we can use a map, however, this impacts runtime.
  // std::unordered_map<int,int> dig_spoken;

  // Add which numbers have been spoken
  for (size_t i = 0; i < input_.size() - 1; i++) {
    dig_spoken[input_[i]] = i + 1;
  }
  // Go through previous digits and see if they have been spoken
  auto prev_dig = input_.back();
  for (int i = input_.size(); i < nth_digit; i++) {
    int num = 0;
    if (dig_spoken[prev_dig] != 0) {
      num = i - dig_spoken[prev_dig];
    }
    dig_spoken[prev_dig] = i;
    prev_dig = num;
  }
  return prev_dig;
}

// Implement part two solution
output_type day15::solve_part2(const input_type &input_) {
  return solve_part1(input_, 30000000);
}
