#include "day1.hpp"

#include "utils.hpp"

using day1::input_type;

input_type day1::transform_input(std::vector<std::string>& input) {
  input_type output;
  for (auto& i : input) {
    output.push_back(

        std::stoi(i));
  }
  return output;
}

input_type day1::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
std::string day1::solve_part1(input_type input_) {
  for (size_t i = 0; i < input_.size() - 1; i++) {
    for (size_t j = i; j < input_.size(); j++) {
      if (input_[i] + input_[j] == 2020) {
        return std::to_string(input_[i] * input_[j]);
      }
    }
  }
  return "Implement part one";
}

// Implement part two solution
std::string day1::solve_part2(input_type input_) {
  for (size_t i = 0; i < input_.size() - 2; i++) {
    for (size_t j = i; j < input_.size() - 1; j++) {
      for (size_t k = j; k < input_.size(); k++) {
        if (input_[i] + input_[j] + input_[k] == 2020) {
          return std::to_string(input_[i] * input_[j] * input_[k]);
        }
      }
    }
  }
  return "Implement part two";
}
