#include <chrono>
#include <iostream>

#include "droid.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
int main() {
  // Part one
  auto begin = steady_clock::now();

  Droid droid(std::string(SOURCE_DIR) + "/data/input.txt");
  auto output = droid.repair_oxygen();
  int part_one = std::get<2>(output);

  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = steady_clock::now();

  int part_two = droid.fill_oxygen(std::get<0>(output), std::get<1>(output));

  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}