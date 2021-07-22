#include <chrono>
#include <iostream>

#include "2019/day23/cpp/include/network.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = steady_clock::now();

  Network network(std::string(SOURCE_DIR) + "/data/input.txt", 50);
  auto output = network.run();
  auto part_one = output.first;

  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  auto part_two = output.second;
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
