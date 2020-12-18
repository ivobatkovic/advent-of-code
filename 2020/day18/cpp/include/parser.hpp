#ifndef _PARSER_H_
#define _PARSER_H_

#include <boost/regex.hpp>
#include <string>
#include <unordered_map>
#include <vector>
class Parser {
  using operator_map = std::unordered_map<int, std::vector<char>>;

 public:
  int max_op_m;
  boost::regex re_number_m, re_operator_m;
  std::unordered_map<int, boost::regex> re_operands_m;

  Parser(operator_map m = operator_map({{0, {'+', '*'}}}), int max_op = 0,
         std::string num = "\\d+", std::string op = "[^\\d]");

  int64_t operate(const int64_t &a, const int64_t &b, const char &op);

  std::string extract_parenthesis(std::string &line);

  int64_t compute_expression(std::string line);

  int64_t evaluate(std::string line);
};

#endif