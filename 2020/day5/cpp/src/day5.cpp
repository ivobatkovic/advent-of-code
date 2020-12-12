#include "day5.hpp"

#include <algorithm>

#include "utils.hpp"
using day5::input_type;

input_type day5::transform_input(std::vector<std::string> &input) {
  input_type output;

  for (auto &inp : input) {
    int row[] = {0, 127};
    int col[] = {0, 7};
    for (auto &seat : inp) {
      if (seat == 'B') {
        row[0] = (row[0] + 1 + row[1]) / 2;
      } else if (seat == 'F') {
        row[1] = (row[0] + row[1]) / 2;
      } else if (seat == 'R') {
        col[0] = (col[0] + 1 + col[1]) / 2;
      } else if (seat == 'L') {
        col[1] = (col[0] + col[1]) / 2;
      }
    }
    output.push_back(row[0] * 8 + col[0]);
  }
  return output;
}

input_type day5::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
std::string day5::solve_part1(const input_type &input_) {
  return std::to_string(*std::max_element(input_.begin(), input_.end()));
  return "Implement part one";
}

// Implement part two solution
std::string day5::solve_part2(const input_type &input_) {
  // Go through input and sort it
  auto sorted = input_;
  std::sort(sorted.begin(), sorted.end());

  for (size_t i = 0; i < sorted.size() - 1; i++) {
    if (abs(sorted[i] - sorted[i + 1]) > 1) {
      return std::to_string(sorted[i] + 1);
    }
  }
  return "Implement part two";
}
