#include "2020/day19/cpp/include/day19.hpp"

#include <boost/algorithm/string.hpp>
#include <regex>

#include "utils/cpp/include/utils.hpp"

using day19::input_type;
using day19::message_type;
using day19::output_type;
using day19::rule_type;

input_type day19::transform_input(std::vector<std::string> &input) {
  // Dictionary to keep the rules and how they are connected
  rule_type rules;

  int row = 0;
  for (auto &inp : input) {
    // After an empty row, we reach the messages
    if (inp.length() == 0) {
      break;
    }

    // Separate rule number from rules
    std::vector<std::string> rls;
    utils::split_string(inp, ":", rls);
    auto rule_nr = rls[0];

    // Check if the following rule is a letter
    std::smatch sm;
    if (std::regex_search(rls[1], sm, std::regex("[a-z]"))) {
      rules[rule_nr].push_back({{sm[0]}});
      // Otherwise, append the sub rules
    } else {
      std::vector<std::string> sub_rules;
      boost::algorithm::trim(rls[1]);
      utils::split_string(rls[1], "|", sub_rules);
      // Append "multiple" rule options
      for (auto &sub_rule : sub_rules) {
        std::vector<std::string> sr;
        boost::algorithm::trim(sub_rule);
        utils::split_string(sub_rule, " ", sr);
        rules[rule_nr].push_back(sr);
      }
    }
    row++;
  }
  // Rest if onput data consists of messages
  message_type messages = {input.begin() + row + 1, input.end()};

  return std::make_tuple(rules, messages);
}

input_type day19::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

bool day19::rule_check(rule_type &rules, const std::string &msg,
                       message_type rule_nums) {
  // If rule_nums is empty: we reached the end of the rule check
  if (rule_nums.size() == 0) {
    //  If the message is empty, all rules passed
    return (msg.length() == 0) ? true : false;
  }
  // Set the first rule as the current one, and keep the remaining
  auto rule_num = rule_nums[0];
  rule_nums = {rule_nums.begin() + 1, rule_nums.end()};

  // Obtain rules to check from the current rule
  auto rules_to_check = rules[rule_num];
  auto first_rule = rules_to_check[0][0];

  // Check if the first rule appearing is a letter
  std::smatch sm;
  if (std::regex_search(first_rule, sm, std::regex("[a-z]"))) {
    // Check if the message starts with the rule, and the rest of the
    // message satisfies all next rules
    bool match = (msg[0] == first_rule[0]);
    return match && rule_check(rules,
                               msg.substr(first_rule.length(),
                                          msg.length() - first_rule.length()),
                               rule_nums);
    // Otherwise, this rule connects to another one
  } else {
    // Check if any group of rules in rules_to_check is satisfied. Note
    // that we append the remaining rule_nums to the number, as we need
    // to continue the search
    for (auto &option : rules_to_check) {
      option.insert(option.end(), rule_nums.begin(), rule_nums.end());
      if (rule_check(rules, msg, option)) {
        return true;
      }
    }
  }
  return false;
}

// Implement part one solution
output_type day19::solve_part1(const input_type &input_) {
  auto [rules, messages] = input_;
  auto s = 0;
  for (auto &msg : messages) {
    s += (rule_check(rules, msg, {"0"})) ? 1 : 0;
  }
  return s;
}

// Implement part two solution
output_type day19::solve_part2(const input_type &input_) {
  auto [rules, messages] = input_;
  rules["8"] = std::vector<std::vector<std::string>>({{"42"}, {"42", "8"}});
  rules["11"] =
      std::vector<std::vector<std::string>>({{"42", "31"}, {"42", "11", "31"}});
  auto s = 0;
  for (auto &msg : messages) {
    s += (rule_check(rules, msg, {"0"})) ? 1 : 0;
  }
  return s;
}
