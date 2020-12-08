#include "day6.hpp"

#include <algorithm>

#include "utils.hpp"
using day6::input_type;

input_type day6::transform_input(std::vector<std::string> &input) {
  input_type group(1, std::vector<std::set<char>>());
  int n_groups(0);

  for (auto &inp : input) {
    if (inp.size() == 0) {
      n_groups++;
      group.push_back(std::vector<std::set<char>>());
    } else {
      std::set<char> inp_set;
      for (auto &letter : inp) {
        inp_set.insert(letter);
      }
      group[n_groups].push_back(inp_set);
    }
  }
  return group;
}

input_type day6::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
std::string day6::solve_part1(input_type input_) {
  size_t n_unique(0);
  for (auto &inp : input_) {
    std::set<char> set, set_;
    for (auto &sets : inp) {
      std::set_union(sets.begin(), sets.end(), set.begin(), set.end(),
                     std::inserter(set_, set_.begin()));
      set = set_;
    }
    n_unique += set.size();
  }
  return std::to_string(n_unique);
}

// Implement part two solution
std::string day6::solve_part2(input_type input_) {
  size_t n_unique(0);
  for (auto &inp : input_) {
    std::set<char> superset = *inp.begin();
    for (auto sets = inp.begin() + 1; sets < inp.end(); sets++) {
      std::set<char> set;
      std::set_intersection(sets->begin(), sets->end(), superset.begin(),
                            superset.end(), std::inserter(set, set.begin()));
      superset = set;
    }
    n_unique += superset.size();
  }
  return std::to_string(n_unique);
}
