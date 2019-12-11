#include<digits.hpp>
#include<iostream>

using std::string;

int main() {

  int start(108457), end(562041);
  string num = Digits::make_monotonic(std::to_string(start));

  int sol1(0), sol2(0);
  while(std::stoi(num) < end) {
    sol1 = Digits::double_digit(num) ? sol1+1 : sol1;
    sol2 = Digits::double_digit_no_adjacent(num) ? sol2+1 : sol2;
    num = Digits::next_monotonic(num);
  }

  std::cout<<"Solution to part one: "<< sol1 << std::endl;
  std::cout<<"Solution to part two: "<< sol2 << std::endl;

  return 0;



}
