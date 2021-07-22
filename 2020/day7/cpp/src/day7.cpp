#include "2020/day7/cpp/include/day7.hpp"

#include <boost/algorithm/string.hpp>
#include <regex>

#include "utils/cpp/include/utils.hpp"

using day7::bag_contents;
using day7::input_type;

input_type day7::transform_input(std::vector<std::string> &input) {
  input_type bag_contains;

  for (auto &sentence : input) {
    std::vector<std::string> split;
    utils::split_string(sentence, "contain", split);
    auto bag = split[0], contents = split[1];

    auto bag_color = std::regex_replace(bag, std::regex("bag(.*)"), "");
    boost::algorithm::trim(bag_color);
    std::vector<std::string> parts;
    utils::split_string(contents, ',', parts);

    std::regex rgx("^\\s+(\\d+)");
    for (auto &part : parts) {
      part = std::regex_replace(part, std::regex("bag.*"), "");
      std::smatch match;
      if (std::regex_search(part, match, rgx)) {
        auto n_bags = match[0];
        auto color =
            part.substr(n_bags.length(), part.length() - n_bags.length());
        boost::algorithm::trim(color);
        bag_contains[bag_color].push_back(
            std::make_pair(color, std::stoi(n_bags)));
      }
    }
  }
  return bag_contains;
}

input_type day7::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

bool day7::contains_bag(const input_type &input_, std::string color) {
  if (input_.count(color)) {
    for (auto &c : input_.at(color)) {
      if (c.first == "shiny gold") {
        return true;
      } else if (contains_bag(input_, c.first)) {
        return true;
      }
    }
  }
  return false;
}

std::string day7::solve_part1(const input_type &input_) {
  int n_colors(0);
  for (auto &inp : input_) {
    n_colors += (contains_bag(input_, inp.first)) ? 1 : 0;
  }
  return std::to_string(n_colors);
}

// Implement part two solution
int day7::bags_in_bag(const input_type &bag, std::string color, int n_bags) {
  if (!bag.count(color)) {
    return n_bags;
  }
  int bags_in_color(0);
  for (auto &i : bag.at(color)) {
    bags_in_color += n_bags * bags_in_bag(bag, i.first, i.second);
  }
  return n_bags + bags_in_color;
}
std::string day7::solve_part2(const input_type &input_) {
  return std::to_string(bags_in_bag(input_, "shiny gold", 1) - 1);
}
