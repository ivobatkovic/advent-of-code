#include "intcode.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int intcode(std::vector<int> & x) {

  for(std::vector<int>::iterator it = x.begin(); it != x.end(); it+=4) {

    // Kill the program
    if (*it == 99) {
      return x[0];
    }
    // Addition
    else if (*it == 1) {
      x[*(it+3)] = x[*(it+1)] + x[*(it+2)];
    }

    // Multiplication
    else if (*it == 2) {
      x[*(it+3)] = x[*(it+1)] * x[*(it+2)];
    }

  }
  // Return after we processed everything
  return x[0];

}

int solve_intcode(std::vector<int> & x,int x0, int x1) {

  // Make a copy
  std::vector<int> x_copy = x;

  // Modify
  x_copy[1] = x0; x_copy[2] = x1;

  return intcode(x_copy);

}

int solve_intcode_extended(std::vector<int> & x, int output) {

  for(int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      if(solve_intcode(x,noun,verb)==output)
        return 100*noun+verb;
    }
  }
  std::cout << "Here";
  return 0;
}

bool readFile(std::string fileName, std::vector<int> & masses) {
  std::ifstream file(fileName);
  if(!file) {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    return false;
  }

  std::string line;
  while(std::getline(file,line,',')) {
    if(line.size()>0)
      masses.push_back(std::stoi(line));
  }
  file.close();
  return true;
}

int main() {

  std::vector<int> x;
  if(readFile("../data.csv",x)) {
    std::cout << "Solution to part one: " <<
      solve_intcode(x,12,2) << std::endl;
    std::cout << "Solution to part two: " <<
      solve_intcode_extended(x,19690720) << std::endl;
  }


  return 0;



}
