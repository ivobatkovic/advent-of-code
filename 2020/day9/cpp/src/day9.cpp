#include "day9.hpp"

#include <algorithm>
#include <unordered_set>

#include "utils.hpp"
using day9::input_type;
using day9::output_type;

input_type day9::transform_input(std::vector<std::string> &input) {
  input_type output;

  for (auto &inp : input) {
    output.push_back(std::stoll(inp));
  }
  return output;
}

input_type day9::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day9::solve_part1(const input_type &input_, int preamble) {
  std::unordered_set<int64_t> preamble_set(input_.begin(),
                                           input_.begin() + preamble);

  for (size_t i = preamble; i < input_.size(); i++) {
    bool valid = false;
    for (auto &num : preamble_set) {
      if (preamble_set.count(input_[i] - num) && input_[i] != 2 * num) {
        valid = true;
        break;
      }
    }
    if (!valid) {
      return input_[i];
    }

    preamble_set.erase(input_[i - preamble]);
    preamble_set.insert(input_[i]);
  }
  // No solution
  return -1;
}

// Implement part two solution
output_type day9::solve_part2(const input_type &input_, int preamble) {
  auto invalid_num = solve_part1(input_, preamble);

  size_t start(0), end(0);
  auto continguous_sum = input_[0];

  while (end < input_.size() - 1) {
    if (continguous_sum < invalid_num) {
      end++;
      continguous_sum += input_[end];
    } else if (continguous_sum == invalid_num) {
      auto min_val =
          *std::min_element(input_.begin() + start, input_.begin() + end + 1);
      auto max_val =
          *std::max_element(input_.begin() + start, input_.begin() + end + 1);
      return min_val + max_val;
    } else {
      continguous_sum -= input_[start];
      start++;
    }
  }
  // No solution
  return -1;
}
