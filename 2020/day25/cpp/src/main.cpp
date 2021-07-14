#include <chrono>
#include <iostream>

#include "2020/day25/cpp/include/day25.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  auto inp_ = day25::read_input();

  // Part one
  auto begin = steady_clock::now();

  auto part_one = day25::solve_part1(inp_);
  std::cout << "Solution to part one: " << part_one << " ";

  auto end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 1;
}
