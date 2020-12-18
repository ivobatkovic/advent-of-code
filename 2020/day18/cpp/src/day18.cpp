#include "day18.hpp"

#include "parser.hpp"
#include "utils.hpp"
using day18::input_type;
using day18::output_type;

input_type day18::transform_input(std::vector<std::string> &input) {
  return input;
}

input_type day18::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day18::solve_part1(const input_type &input_) {
  Parser p(std::unordered_map<int, std::vector<char>>({{0, {'+', '*'}}}), 0);

  int64_t s = 0;
  for (auto &inp : input_) {
    s += p.evaluate(inp);
  }
  return s;
}

// Implement part two solution
output_type day18::solve_part2(const input_type &input_) {
  Parser p(std::unordered_map<int, std::vector<char>>({
               {0, {'+'}},
               {1, {'*'}},
           }),
           1);

  int64_t s = 0;

  for (auto &inp : input_) {
    s += p.evaluate(inp);
  }
  return s;
}
