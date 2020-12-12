#include "day10.hpp"

#include <algorithm>

#include "utils.hpp"

using day10::input_type;
using day10::output_type;

input_type day10::transform_input(std::vector<std::string> &input) {
  input_type output;
  for (auto &inp : input) {
    output.push_back(std::stoi(inp));
  }
  return output;
}

input_type day10::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

input_type day10::sort_input(const input_type &input) {
  auto sorted = input;
  std::sort(sorted.begin(), sorted.end());
  sorted.insert(sorted.begin(), 0);
  sorted.push_back(sorted.back() + 3);
  return sorted;
}

// Implement part one solution
output_type day10::solve_part1(const input_type &input_) {
  auto data = sort_input(input_);
  int diff1(0), diff3(0);

  for (size_t i = 0; i < data.size() - 1; i++) {
    auto diff = data[i + 1] - data[i];
    if (diff == 3) {
      diff3++;
    } else if (diff == 1) {
      diff1++;
    }
  }
  return diff1 * diff3;
}

// Implement part two solution
output_type day10::solve_part2(const input_type &input_) {
  auto data = sort_input(input_);

  std::vector<output_type> d(data.size() - 1, 0);
  d.push_back(1);
  std::vector<int> steps({1, 2, 3});

  for (int i = int(data.size() - 1); i > 0; i--) {
    for (auto &step : steps) {
      if ((i - step) > -1 && ((data[i] - data[i - step]) <= 3)) {
        d[i - step] += d[i];
      }
    }
  }
  return d[0];
}
