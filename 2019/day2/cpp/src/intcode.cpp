#include "intcode.hpp"
#include "utils.hpp"
#include <iostream>

Intcode::Intcode(bool reset) : m_file_name(), m_memory(), m_reset(reset) {}

Intcode::Intcode(std::string file_name, bool reset) : 
   m_file_name(), m_memory(), m_reset(reset)
{

  std::vector<std::vector<int>> input_memory;
  utils::readCSVFile(file_name,input_memory);
  m_memory = input_memory[0];
}

// Operator () runs the program until termination
int Intcode::operator()()
{
  std::vector<int> x = m_memory;
  
  for(auto it = x.begin(); it < x.end(); it+=4) {

    if (*it == 99) {
      // Update memory
      if (!m_reset) {
        m_memory = x;
      }
      return x[0];
    }
    // Addition
    else if (*it == 1) {
      x[*(it + 3)] = x[*(it + 1)] + x[*(it + 2)];
    }
    // Multiplication
    else if (*it == 2)
    {
      x[*(it + 3)] = x[*(it + 1)] * x[*(it + 2)];
    }
  }
  
  // Update memory
  if (!m_reset)
    m_memory = x;

  return x[0];
}
