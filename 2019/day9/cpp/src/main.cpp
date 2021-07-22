#include <chrono>
#include <iostream>

#include "2019/day5/cpp/include/intcode.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = std::chrono::steady_clock::now();

  Intcode ic(std::string(SOURCE_DIR) + "/data/input.txt", {}, false, false);
  std::cout << "Solution to part one: " << std::get<1>(ic(1)) << " ";

  auto end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part  two
  begin = std::chrono::steady_clock::now();

  ic = Intcode(std::string(SOURCE_DIR) + "/data/input.txt", {}, false, false);
  std::cout << "Solution to part two: " << std::get<1>(ic(2)) << " ";

  end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
