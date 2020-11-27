#include<iostream>
#include "asci.hpp"
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {

  // Part one
  auto begin = steady_clock::now();

  Asci asci = Asci(std::string(SOURCE_DIR) + "/data/input.csv");
  auto part_one = asci.compute_intersections();
  
  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part two
  begin = steady_clock::now();

  auto part_two = asci.collect_dust(true);
  
  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}