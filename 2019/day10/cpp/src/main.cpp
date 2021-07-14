#include <chrono>
#include <iostream>

#include "2019/day10/cpp/include/monitorstation.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = steady_clock::now();

  MonitorStation station(std::string(SOURCE_DIR) + "/data/input.txt");
  std::tuple<int, int> part_one = station.compute_vision(station.m_input);

  auto end = steady_clock::now();

  std::cout << "Solution to part one: " << std::get<0>(part_one) << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = steady_clock::now();

  int part_two = station.blast(station.m_input, std::get<1>(part_one), 200);

  end = steady_clock::now();

  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}