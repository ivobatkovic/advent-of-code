#include <chrono>
#include <iostream>

#include "2019/day2/cpp/include/intcode.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

// Replace the memory at position 1 and 2 with x1 and x2
static int part_one(int x1, int x2) {
  Intcode intcode(std::string(SOURCE_DIR) + "/data/input.txt");

  intcode.m_memory[1] = x1, intcode.m_memory[2] = x2;

  return intcode();
}

// Loop through noun and verbs until the output matches the desired one
static int part_two(int desired_output) {
  Intcode intcode(std::string(SOURCE_DIR) + "/data/input.txt");

  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      intcode.m_memory[1] = noun, intcode.m_memory[2] = verb;
      if (intcode() == desired_output) {
        return 100 * noun + verb;
      }
    }
  }
  return 0;
}

int main() {
  // Part one
  auto begin = std::chrono::steady_clock::now();

  auto sol_part_one = part_one(12, 2);
  std::cout << "Solution to part one: " << sol_part_one << " ";

  auto end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = std::chrono::steady_clock::now();

  auto sol_part_two = part_two(19690720);
  std::cout << "Solution to part two: " << sol_part_two << " ";

  end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}