#include "fuel_counter.hpp"

#include <math.h>

#include "utils.hpp"

// Default constructor
FuelCounter::FuelCounter() : m_masses() {}

// Constructor to read the file input
FuelCounter::FuelCounter(std::string file_name) : m_masses() {
  auto input = utils::read_file(file_name);
  for (auto & inp : input) {
    m_masses.push_back(std::stoi(inp));
  }
  // utils::read_file(file_name, m_masses);
}

// Iterate over the vector of masses
int FuelCounter::fuel_counter(std::vector<int> &masses_) {
  int fuel = 0;
  for (std::vector<int>::iterator it = masses_.begin(); it != masses_.end();
       it++) {
    fuel += fuel_counter(*it);
  }
  return fuel;
}

// Compute the fuel needed for a single mass
int FuelCounter::fuel_counter(int mass) {
  return std::max((int)(floor(mass / 3.0) - 2), 0);
}

// Iterate over the vector of masses and include weight of fuel
int FuelCounter::fuel_counter_extended(std::vector<int> &masses_) {
  int fuel = 0;
  for (std::vector<int>::iterator it = masses_.begin(); it != masses_.end();
       it++) {
    fuel += fuel_needed_total(*it);
  }
  return fuel;
}

// Account for the weight of the fuel
int FuelCounter::fuel_needed_total(int mass_) {
  int required_fuel = fuel_counter(mass_);
  if (required_fuel > 0)
    return required_fuel + fuel_needed_total(required_fuel);
  return 0;
}
