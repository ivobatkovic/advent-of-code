#include "day2.hpp"

#include <algorithm>

#include "utils.hpp"

using day2::input_type;

input_type day2::transform_input(std::vector<std::string> &input) {
  input_type output;

  for (auto &inp : input) {
    std::vector<std::string> split_input;

    inp.erase(std::remove(inp.begin(), inp.end(), ':'), inp.end());
    utils::split_string(inp, ' ', split_input);
    auto count = split_input[0], letter = split_input[1], pw = split_input[2];

    std::vector<std::string> split_count;
    utils::split_string(count, '-', split_count);
    int low = std::stoi(split_count[0]), high = std::stoi(split_count[1]);

    output.push_back(std::make_tuple(low, high, letter[0], pw));
  }

  return output;
}

input_type day2::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
std::string day2::solve_part1(const input_type &input_) {
  int n_pws(0);
  for (auto &[low, high, letter, pw] : input_) {
    auto n_matches = std::count(pw.begin(), pw.end(), letter);
    n_pws += (low <= n_matches && n_matches <= high) ? 1 : 0;
  }
  return std::to_string(n_pws);
}

// Implement part two solution
std::string day2::solve_part2(const input_type &input_) {
  int n_pws(0);
  for (auto &i : input_) {
    auto low = std::get<0>(i), high = std::get<1>(i);
    auto letter = std::get<2>(i);
    auto pw = std::get<3>(i);

    n_pws += (pw[low - 1] == letter) ^ (pw[high - 1] == letter) ? 1 : 0;
  }
  return std::to_string(n_pws);
}
