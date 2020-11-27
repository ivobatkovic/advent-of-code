#include<iostream>
#include "intcode.hpp"
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;


static int solve_puzzle(int input_) {
  Intcode intcode(std::string(SOURCE_DIR) + "/data/input.csv",
      {input_}, false, false);

  while (true) {
    auto output = intcode();
    if (std::get<0>(output)) {
      return std::get<1>(output);
    }
  }
}

int main() {

  // Part one
  auto begin = std::chrono::steady_clock::now();
  std::cout << "Solution to part one: " << solve_puzzle(1) << " ";
  auto end = std::chrono::steady_clock::now();
  std::cout << "(time taken " <<
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = std::chrono::steady_clock::now();
  std::cout << "Solution to part two: " << solve_puzzle(5) << " ";
  end = std::chrono::steady_clock::now();
  std::cout << "(time taken " <<
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";
  

  return 0;
}