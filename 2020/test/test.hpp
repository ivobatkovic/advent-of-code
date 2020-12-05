#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include<iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>


// Input type i'm going to parse into for each day
// After bootstrapping, this needs to be modified
using t_type = std::vector<std::string>;

auto inline transform_input(std::vector<std::string> &input) {
  return input;
}

auto inline read_input(std::string fileName) -> decltype(t_type()){

  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    std::exit(-1);
  }
  std::string line;
  std::vector<std::string> x;
  while (std::getline(file, line)) {
    x.push_back(line);
  }
  file.close();
  return transform_input(x);
}

std::string solve_part1(t_type input);

std::string solve_part2(t_type input);


#endif