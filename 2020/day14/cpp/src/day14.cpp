#include "day14.hpp"
#include "utils.hpp"

using day14::input_type;
using day14::output_type;

input_type day14::transform_input(std::vector<std::string> &input) {
  return input;
}

input_type day14::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day14::solve_part1(const input_type &input_) {
  std::cout << typeid(input_).name() << std::endl;
  return "Implement part one";
}

// Implement part two solution
output_type day14::solve_part2(const input_type &input_) {
  std::cout << typeid(input_).name() << std::endl;
  return "Implement part two";
}

