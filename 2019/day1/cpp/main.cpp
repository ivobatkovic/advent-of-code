#include <chrono>
#include <iostream>

#include "solutions.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  const std::string input = day1::read_input();

  auto begin = steady_clock::now();

  const auto part_one = day1::solve_part1(input);
  std::cout << "Solution to part one: " << part_one << " ";

  auto end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  begin = steady_clock::now();

  const auto part_two = day1::solve_part2(input);
  std::cout << "Solution to part two: " << part_two << " ";

  end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
