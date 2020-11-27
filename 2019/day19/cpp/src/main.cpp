#include<iostream>
#include "beam.hpp"
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {

  auto begin = steady_clock::now();
  Beam beam(std::string(SOURCE_DIR) + "/data/input.csv");
  auto part_one = beam.part_one();
  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";
  
  begin = steady_clock::now();
  auto part_two = beam.part_two();
  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
