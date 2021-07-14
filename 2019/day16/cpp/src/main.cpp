#include <chrono>
#include <iostream>

#include "2019/day16/cpp/include/fft.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {
  // Part one
  auto begin = steady_clock::now();

  FFT fft = FFT(std::string(SOURCE_DIR) + "/data/input.txt");
  auto part_one = fft.part_one();

  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = steady_clock::now();

  auto part_two = fft.part_two();

  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken "
            << duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}