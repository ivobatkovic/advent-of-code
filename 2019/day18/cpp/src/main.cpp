#include<iostream>
#include "maze.hpp"
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
int main() {

  // Part one
  auto begin = steady_clock::now();
  
  Maze maze(std::string(SOURCE_DIR) + "/data/input.txt");
  auto part_one = maze.compute_shortest_path();
  
  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";
  
  // Part two
  begin = steady_clock::now();
  
  maze = Maze(std::string(SOURCE_DIR) + "/data/input.txt", true);
  auto part_two =  maze.compute_shortest_path();
  
  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
