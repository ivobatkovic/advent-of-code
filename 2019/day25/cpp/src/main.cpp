#include<iostream>
#include "cryo.hpp"
#include <chrono>

int main() {

  Cryo cryo(std::string(SOURCE_DIR) + "/data/input.csv");
  cryo.play();
      
  return 0;
}
