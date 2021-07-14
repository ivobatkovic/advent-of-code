#include <chrono>
#include <iostream>

#include "2019/day8/cpp/include/spaceimage.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = std::chrono::steady_clock::now();

  SpaceImage img(std::string(SOURCE_DIR) + "/data/input.txt", 25, 6);
  std::cout << "Solution to part one: " << img.corruption_check() << " ";

  auto end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = std::chrono::steady_clock::now();

  std::cout << "Solution to part two: \n";
  img.print_image(img.reconstruct_image());

  end = std::chrono::steady_clock::now();
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}