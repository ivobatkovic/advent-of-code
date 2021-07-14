#include "2020/day4/cpp/include/day4.hpp"

#include <regex>
#include <set>

#include "utils/cpp/include/utils.hpp"

using day4::input_type;

input_type day4::transform_input(std::vector<std::string> &input) {
  input_type passports({std::map<std::string, std::string>()});
  int n_passports(0);
  for (auto &inp : input) {
    if (inp.size() == 0) {
      passports.push_back(std::map<std::string, std::string>());
      n_passports++;
    } else {
      std::vector<std::string> parts;
      utils::split_string(inp, ' ', parts);
      for (auto &part : parts) {
        std::vector<std::string> key_value;
        utils::split_string(part, ':', key_value);
        passports[n_passports][key_value[0]] = key_value[1];
      }
    }
  }
  return passports;
}

input_type day4::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
std::string day4::solve_part1(const input_type &input_) {
  // Required fields
  std::string req[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
  std::set<std::string> req_set(std::begin(req), std::end(req));

  auto n_matches(0);
  for (auto &inp : input_) {
    std::set<std::string> inp_set;
    for (auto &i : inp) {
      inp_set.insert(i.first);
    }

    if (std::includes(inp_set.begin(), inp_set.end(), req_set.begin(),
                      req_set.end())) {
      n_matches++;
    }
  }
  return std::to_string(n_matches);
}

// Implement part two solution
std::string day4::solve_part2(const input_type &input_) {
  std::map<std::string, std::string> rgx = {
      {"byr", "^(19[2-9]\\d|200[0-2])$"},
      {"iyr", "^20(1\\d|20)"},
      {"eyr", "^20(2\\d|30)"},
      {"hgt", "^(1([5-8]\\d|9[0-3])cm|(59|6\\d|7[0-6])in)$"},
      {"hcl", "^#[\\da-f]{6}"},
      {"ecl", "^(amb|blu|brn|gry|grn|hzl|oth)$"},
      {"pid", "^(\\d{9})$"},
      {"cid", "^(.*)"}};

  int n_matches(0);
  for (auto &inp : input_) {
    size_t rgx_matches(0);
    for (auto &mp : inp) {
      rgx_matches +=
          (std::regex_match(mp.second, std::regex(rgx[mp.first]))) ? 1 : 0;
    }
    n_matches +=
        (rgx_matches == inp.size() && solve_part1({inp}) == "1") ? 1 : 0;
  }
  return std::to_string(n_matches);
}