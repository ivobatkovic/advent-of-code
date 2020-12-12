#include "day3.hpp"

#include "utils.hpp"

using day3::input_type;

input_type day3::transform_input(std::vector<std::string> &input) {
  return input;
}

input_type day3::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
std::string day3::solve_part1(const input_type &input_) {
  auto w = input_[0].size();
  int n_trees(0);
  for (size_t y = 0; y < input_.size() - 1; y++) {
    n_trees += (input_[y + 1][(y + 1) * 3 % w] == '#') ? 1 : 0;
  }
  return std::to_string(n_trees);
  return "Implement part one";
}

// Implement part two solution
std::string day3::solve_part2(const input_type &input_) {
  auto w = input_[0].size();

  std::vector<float> x_diff({1, 3, 5, 7, 0.5});
  std::vector<float> y_diff({1, 1, 1, 1, 2});

  int64_t prod_trees(1);
  for (size_t i = 0; i < x_diff.size(); i++) {
    auto n_trees(0);
    auto dx = x_diff[i], dy = y_diff[i];
    for (size_t y = 0; y < input_.size() - 1; y += dy) {
      n_trees += (input_[int(y + dy)][int((y + dy) * dx) % w] == '#') ? 1 : 0;
    }
    prod_trees *= n_trees;
  }
  return std::to_string(prod_trees);
}
