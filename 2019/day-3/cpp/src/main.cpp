
#include "crossed_wires.hpp"
int main() {

  CrossedWires wire = CrossedWires("../data.csv");
  std::cout<<"Solution to part one: "<< wire.manhattan_distance << std::endl;
  std::cout<<"Solution to part two: "<< wire.n_steps << std::endl;

  return 0;



}
