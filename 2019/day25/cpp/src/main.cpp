#include <chrono>
#include <iostream>

#include "cryo.hpp"

int main() {
  Cryo cryo(std::string(SOURCE_DIR) + "/data/input.txt");
  cryo.play();

  return 0;
}
