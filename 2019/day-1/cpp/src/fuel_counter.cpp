#include "fuel_counter.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int fuel_counter(std::vector<int> & masses) {
  int fuel = 0;
  for(std::vector<int>::iterator it = masses.begin();
      it != masses.end(); it++) {
    fuel += fuel_counter(*it);
  }
  return fuel;
}
int fuel_counter(int mass) {
  return std::max((int)(std::floor(mass/3.0)-2),0);
}

int fuel_counter_extended(std::vector<int> & masses) {
  int fuel = 0;
  for(std::vector<int>::iterator it = masses.begin();
      it != masses.end(); it++) {
    fuel += fuel_needed_total(*it);
  }
  return fuel;
}

int fuel_needed_total(int mass) {
  int required_fuel = fuel_counter(mass);
  if (required_fuel > 0)
    return required_fuel + fuel_needed_total(required_fuel);
  return 0;
}

bool readFile(std::string fileName, std::vector<int> & masses) {
  std::ifstream file(fileName);
  if(!file) {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    return false;
  }

  std::string line;
  while(std::getline(file,line)) {
    if(line.size()>0)
      masses.push_back(std::stoi(line));
  }
  file.close();
  return true;
}

int main() {

  std::vector<int> masses;
  if(readFile("../data.txt",masses)) {
    std::cout<<"Fuel needed for part one: " <<
      fuel_counter(masses) << std::endl;
    std::cout<<"Fuel needed for part one: " <<
      fuel_counter_extended(masses) << std::endl;
  }

  return 0;


  
}