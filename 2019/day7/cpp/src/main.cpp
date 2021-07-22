#include <chrono>
#include <iostream>
#include <unordered_set>

#include "2019/day7/cpp/include/amplifier.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  std::string file_name = std::string(SOURCE_DIR) + "/data/input.txt";

  // Part one
  auto begin = std::chrono::steady_clock::now();
  std::cout << "Solution to part one: "
            << Amplifier::get_maximum_thrust(file_name) << " ";

  auto end = std::chrono::steady_clock::now();

  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = std::chrono::steady_clock::now();
  std::cout << "Solution to part two: " << Amplifier::feedback_thrust(file_name)
            << " ";
  end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}