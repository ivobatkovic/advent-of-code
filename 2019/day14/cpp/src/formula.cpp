#include "formula.hpp"

#include "utils.hpp"
#include <math.h>

#include <iostream>
#include <regex>

Formula::Formula(std::string file_name) : m_formula() {
  initialize_formula(file_name);
}

void Formula::initialize_formula(std::string file_name) {

  auto form = utils::read_file(file_name);

  // Regex to separeate left-hand and right-hand side with "=>"
  std::regex rgx("([^=>]+)");
  for (auto f : form) {
    std::smatch sm;
    std::vector<std::string> parts;
    while (regex_search(f, sm, rgx)) {
      parts.push_back(sm[0]);
      f = sm.suffix();
    }

    // Split the left-hand and right-hand sides into parts
    std::vector<std::string> LHS, rhs;
    utils::split_string(parts[0], ',', LHS);
    utils::split_string(parts[1], ' ', rhs);

    // Go through the left hand side assign the formula dependency
    for (auto lhs : LHS) {
      std::vector<std::string> t;
      utils::split_string(lhs, ' ', t);
      m_formula[t[1]].push_back(
          std::make_tuple(std::stoi(t[0]), std::stoi(rhs[0]), rhs[1]));
    }
  }
}

// Figure out how much fuel is needed to generate a specific "key"
int64_t Formula::compute(std::string key, int64_t amount) {
  if (key == "FUEL") {
    return amount;
  }

  int64_t s = 0;
  for (auto &form : m_formula[key]) {
    auto total = compute(std::get<2>(form), amount);
    s += (std::ceil(total / double(std::get<1>(form))) * std::get<0>(form));
  }
  return s;
}

// Figure out how much fuel can be generated, given <ore>
int64_t Formula::compute_fuel(int64_t ore) {
  int64_t fuel_min(ore / compute("ORE", 1)), fuel_max(ore);

  while ((fuel_max - fuel_min) > 1) {
    int64_t mid = (fuel_min + fuel_max) / int64_t(2);

    if (compute("ORE", mid) <= ore) {
      fuel_min = mid;
    } else {
      fuel_max = mid;
    }
  }
  return fuel_min;
}