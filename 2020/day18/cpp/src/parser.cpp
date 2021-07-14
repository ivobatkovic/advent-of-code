#include "2020/day18/cpp/include/parser.hpp"

#include <boost/algorithm/string/replace.hpp>
#include <iostream>

Parser::Parser(std::unordered_map<int, std::vector<char>> m, int max_op,
               std::string num_, std::string op_)
    : max_op_m(max_op),    // Default number of preceding rules
      re_number_m(num_),   // Default regex for finding numbers
      re_operator_m(op_),  // Default regex for finding operator
      re_operands_m() {
  // Regex to access operands for an operator: "123+456" -> "123","+", "456"
  // Here, we set the operator precedence
  for (int o = 0; o < max_op_m + 1; o++) {
    std::string rg;
    for (auto &op : m[o]) {
      rg += "\\" + std::string(1, op) + "|";
    }
    rg = rg.substr(0, rg.length() - 1);
    re_operands_m[o] = boost::regex("(-?\\d+)([" + rg + "])(-?\\d+)");
  }
}

// Apply operation
int64_t Parser::operate(const int64_t &a, const int64_t &b, const char &op) {
  if (op == '+') {
    return a + b;
  } else if (op == '*') {
    return a * b;
  } else {
    std::cout << "Fail\n";
    return -1;
  }
}
// Extract, e.g., "a+(b*(c+d)+f)+f"->"(b*(c+d)+f)""
std::string Parser::extract_parenthesis(std::string &line) {
  // Stop when we find a closing parenthesis
  std::vector<int> open_id, close_id;
  auto found_parenthesis(false);
  for (size_t i = 0; i < line.length(); i++) {
    if (line[i] == '(') {
      open_id.push_back(i);
    }
    if (line[i] == ')') {
      close_id.push_back(i);
      if (close_id.size() == open_id.size()) {
        found_parenthesis = true;
        break;
      }
    }
  }
  if (found_parenthesis) {
    return line.substr(open_id[0], close_id.back() + 1 - open_id[0]);
  }
  return std::string();
}

int64_t Parser::compute_expression(std::string line) {
  // Padding to handle minus sign
  boost::replace_all(line, "-", "+-");

  // Go through the operators in priority order
  for (int i = 0; i < max_op_m + 1; i++) {
    // Keep going until all operations are completed
    while (true) {
      boost::smatch sm;
      std::vector<std::string> m;
      if (boost::regex_search(line, sm, re_operands_m[i])) {
        for (auto s : sm) {
          m.push_back(s);
        }
        auto cm = operate(std::stoll(m[1]), std::stoll(m[3]), m[2][0]);
        boost::replace_all(line, m[0], std::to_string(cm));
      } else {
        break;
      }
    }
  }
  // After all operations are done, we should have a number
  if (boost::regex_match(line, boost::regex("^\\d+$"))) {
    return std::stoll(line);
  }
  // Otherwise, something went wrong
  return -1;
}

int64_t Parser::evaluate(std::string line) {
  // Make sure that any spaces are removed
  boost::replace_all(line, " ", "");

  // Find parenthes and evaulate them
  while (true) {
    // Get a closed parenthesis
    auto parenthesis = extract_parenthesis(line);
    if (parenthesis.length() == 0) {
      break;
    }
    // Compute its contents
    auto parse_parenthesis =
        evaluate(parenthesis.substr(1, parenthesis.length() - 2));
    // Replace the expression
    boost::replace_all(line, parenthesis, std::to_string(parse_parenthesis));
  }
  return compute_expression(line);
}