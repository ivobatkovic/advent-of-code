#include "2019/day4/cpp/include/digits.hpp"
#include <chrono>
#include <iostream>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

using std::string;

int main() {
  // Part one & two
  auto begin = std::chrono::steady_clock::now();

  int start_digit(108457), end_digit(562041);
  string num = Digits::make_monotonic(std::to_string(start_digit));

  int sol1(0), sol2(0);
  while (std::stoi(num) < end_digit) {
    sol1 = Digits::double_digit(num) ? sol1 + 1 : sol1;
    sol2 = Digits::double_digit_no_adjacent(num) ? sol2 + 1 : sol2;
    num = Digits::next_monotonic(num);
  }

  auto end = std::chrono::steady_clock::now();

  std::cout << "Solution to part one: " << sol1 << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  std::cout << "Solution to part two: " << sol2 << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
