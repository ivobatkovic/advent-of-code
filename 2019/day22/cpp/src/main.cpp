#include<iostream>
#include "deck.hpp"
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {

  // Part one
  auto begin = steady_clock::now();
  
  Deck deck(std::string(SOURCE_DIR) + "/data/input.txt", 10007);
  auto part_one = deck.part_one(2019);
  
  auto end = steady_clock::now();
  std::cout << "Solution to part one: " << part_one << " ";
  std::cout << "(time taken " <<
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  // Part  two
  begin = steady_clock::now();
  
  deck = Deck(std::string(SOURCE_DIR) + "/data/input.txt", 119315717514047);
  auto part_two = deck.part_two(2020, 101741582076661);
  
  end = steady_clock::now();
  std::cout << "Solution to part two: " << part_two << " ";
  std::cout << "(time taken " << 
      duration_cast<milliseconds>(end - begin).count() << "[ms])\n";

  return 0;
}
