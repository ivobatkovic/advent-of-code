#include <chrono>
#include <iostream>

#include "fuel_counter.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = steady_clock::now();

  FuelCounter counter(std::string(SOURCE_DIR) + "/data/input.txt");
  auto part_one = counter.fuel_counter(counter.m_masses);
  std::cout << "Solution to part one: " << part_one << " ";

  auto end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = steady_clock::now();

  auto part_two = counter.fuel_counter_extended(counter.m_masses);
  std::cout << "Solution to part two: " << part_two << " ";

  end = steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";
  return 0;
}