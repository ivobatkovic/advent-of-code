#include "2020/day13/cpp/include/day13.hpp"

#include <math.h>

#include "utils/cpp/include/utils.hpp"
using day13::input_type;
using day13::output_type;

input_type day13::transform_input(std::vector<std::string> &input) {
  input_type output;

  for (auto &row : input) {
    std::vector<std::string> split;
    utils::split_string(row, ",", split);
    for (auto &digit : split) {
      output.push_back(digit);
    }
  }
  return output;
}

input_type day13::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day13::solve_part1(const input_type &input_) {
  // First element is the time stamp
  float timestamp = std::stoi(input_[0]);

  // Waiting time, and corresponding id
  std::vector<int64_t> wait({WINT_MAX, 0});

  // Go through all ids
  for (auto it = input_.begin() + 1; it < input_.end(); it++) {
    if (*it == "x") {
      continue;
    }
    // Id and departure time
    auto id = std::stoi(*it);
    int64_t dep_time = id * ceil(timestamp / id);

    // Check if departure time after time stamp and update minimum wait time
    if ((dep_time >= timestamp) && (dep_time < wait[0])) {
      wait = std::vector<int64_t>({dep_time, id});
    }
  }
  return (wait[0] - timestamp) * wait[1];
}

// Implement part two solution
output_type day13::solve_part2(const input_type &input_) {
  // Get first digit (skip the timestamp)
  auto id = std::stoi(input_[1]);

  // Starting time step, and cycle for reapeating
  int64_t i(1), cycle(1);

  // Get the offset andstarting id
  for (size_t offset = 1; offset < input_.size() - 1; offset++) {
    auto next_id = input_[offset + 1];

    if (next_id == "x") {
      continue;
    }
    // Check if we can find a multiple between id and next_id
    while (true) {
      // multiple * next_id + offset = id * j
      auto multiple = double(i * id + offset) / std::stoi(next_id);

      // if multiple is a positive integer, we found a match
      if (fmod(multiple, 1) < 1e-6 && multiple > 0) {
        break;
      }
      // Otherwise, keep going in cycle
      i += cycle;
    }
    // If we found a match, we need update the cycle of how frequently this
    // combination occurs
    cycle *= std::stoll(next_id);
  }
  return i * id;
}
