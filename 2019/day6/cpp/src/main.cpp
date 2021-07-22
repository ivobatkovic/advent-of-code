#include <chrono>
#include <iostream>

#include "2019/day6/cpp/include/orbit.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = std::chrono::steady_clock::now();

  Orbit orbit(std::string(SOURCE_DIR) + "/data/input.txt");
  std::cout << "Solution to part one: " << orbit.get_number_of_orbits() << " ";
  auto end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = std::chrono::steady_clock::now();
  std::cout << "Solution to part two: " << orbit.get_orbitals("YOU", "SAN")
            << " ";
  end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}