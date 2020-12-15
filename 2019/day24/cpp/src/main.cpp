#include <chrono>
#include <iostream>

#include "planet.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  auto begin = steady_clock::now();
  Planet planet(std::string(SOURCE_DIR) + "/data/input.txt");
  auto part_one = planet.part_one();
  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  begin = steady_clock::now();
  Planet planet2(std::string(SOURCE_DIR) + "/data/input.txt", true);
  auto part_two = planet2.part_two();
  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
