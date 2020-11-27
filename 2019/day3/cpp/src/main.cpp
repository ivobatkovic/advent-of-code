#include "wires.hpp"
#include <chrono>
#include <iostream>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main() {

  // Part one &  two
  auto begin = std::chrono::steady_clock::now();

  // Read input file and let the constructor compute the intersections
  Wires wire(std::string(SOURCE_DIR) + "/data/input.csv");
  wire.solve();

  auto end = std::chrono::steady_clock::now();
  
  std::cout<<"Solution to part one: "<< wire.m_distance << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  std::cout<<"Solution to part two: "<< wire.m_steps << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";
  

  return 0;
}
