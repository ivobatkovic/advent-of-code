#include <chrono>
#include <iostream>

#include "2019/day11/cpp/include/paint.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = steady_clock::now();

  Intcode ic(std::string(SOURCE_DIR) + "/data/input.txt", {}, false, false);
  pairmap map;
  auto part_one = Paint::get_painted_tiles(map, ic);

  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = steady_clock::now();

  ic = Intcode(std::string(SOURCE_DIR) + "/data/input.txt", {}, false, false);
  pairmap map2;
  map2[std::pair<int, int>(0, 0)] = "#";
  Paint::get_painted_tiles(map2, ic);

  end = steady_clock::now();
  std::cout << "Solution to part two: \n";
  Paint::paint_map(map2);
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}