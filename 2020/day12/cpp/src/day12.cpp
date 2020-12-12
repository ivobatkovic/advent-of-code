#include "day12.hpp"

#include "utils.hpp"

using day12::input_type;
using day12::output_type;

input_type day12::transform_input(std::vector<std::string> &input) {
  return input;
}

input_type day12::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day12::solve_part1(input_type input_) {
  std::cout << typeid(input_).name() << std::endl;
  return "Implement part one";
}

// Implement part two solution
output_type day12::solve_part2(input_type input_) {
  std::cout << typeid(input_).name() << std::endl;
  return "Implement part two";
}
