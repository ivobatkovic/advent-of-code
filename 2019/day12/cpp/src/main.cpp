#include <chrono>
#include <iostream>

#include "2019/day12/cpp/include/gravity.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {
  // Part one
  auto begin = std::chrono::steady_clock::now();

  Gravity grav = Gravity(std::string(SOURCE_DIR) + "/data/input.txt");
  grav.update(1000);
  auto part_one = grav.energy();

  auto end = std::chrono::steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = std::chrono::steady_clock::now();

  grav = Gravity(std::string(SOURCE_DIR) + "/data/input.txt");
  auto part_two = grav.compute_cycles();

  end = std::chrono::steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}