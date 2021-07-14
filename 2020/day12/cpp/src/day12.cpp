#include "2020/day12/cpp/include/day12.hpp"

#include <complex>
#include <unordered_map>

#include "utils/cpp/include/utils.hpp"
using day12::input_type;
using day12::output_type;

using complex_map = std::unordered_map<char, std::complex<double>>;

input_type day12::transform_input(std::vector<std::string> &input) {
  input_type output;
  for (auto &inp : input) {
    output.push_back({inp[0], std::stoi(inp.substr(1, inp.size() - 1))});
  }
  return output;
}

input_type day12::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day12::solve_part1(const input_type &input_) {
  int pos[2] = {0, 0};
  int dx[2] = {1, 0};

  for (auto &action_value : input_) {
    auto action = action_value.first;
    auto value = action_value.second;

    if (action == 'N' || action == 'S') {
      int v = (action == 'N') ? 1 : -1;
      pos[1] += v * value;
    } else if (action == 'W' || action == 'E') {
      int v = (action == 'E') ? 1 : -1;
      pos[0] += v * value;
    } else if (action == 'L' || action == 'R') {
      int v = (action == 'L') ? 1 : -1;
      for (int i = 0; i < (value / 90); i++) {
        auto t = dx[1];
        dx[1] = v * dx[0];
        dx[0] = -v * t;
      }
    } else {
      pos[0] += value * dx[0];
      pos[1] += value * dx[1];
    }
  }
  return std::abs(pos[0]) + std::abs(pos[1]);
}

// Implement part two solution
output_type day12::solve_part2(const input_type &input_) {
  int pos[2] = {0, 0};
  int wp[2] = {10, 1};

  for (auto &action_value : input_) {
    auto action = action_value.first;
    auto value = action_value.second;

    if (action == 'N' || action == 'S') {
      int v = (action == 'N') ? 1 : -1;
      wp[1] += v * value;
    } else if (action == 'W' || action == 'E') {
      int v = (action == 'E') ? 1 : -1;
      wp[0] += v * value;
    } else if (action == 'L' || action == 'R') {
      int v = (action == 'L') ? 1 : -1;
      for (int i = 0; i < (value / 90); i++) {
        auto t = wp[1];
        wp[1] = v * wp[0];
        wp[0] = -v * t;
      }
    } else {
      pos[0] += value * wp[0];
      pos[1] += value * wp[1];
    }
  }
  return std::abs(pos[0]) + std::abs(pos[1]);
}
