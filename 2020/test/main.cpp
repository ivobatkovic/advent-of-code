#include "test.hpp"
#include <iostream>

int main() {

  auto inp_ = read_input("../day1/data/test_input0.txt");

  std::cout << solve_part1(inp_);
  std::cout << solve_part2(inp_);

  
  return 1;
}