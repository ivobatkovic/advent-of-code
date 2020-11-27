#include "utils.hpp"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

using std::vector;
using std::string;

// Instantiate templates for the different types
template bool utils::readFile(string, vector<int64_t> &);
template bool utils::readFile(string, vector<int> &);
template bool utils::readFile(string, vector<string> &);

template<typename T>
bool utils::readFile(string fileName, vector<T> &x)
{
  std::ifstream file(fileName);
  if (!file)
  {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    std::exit(-1);
  }
  string line;
  while (std::getline(file, line)) {
    if (line.size() > 0) {
      // If the template is a string, preserve whitespaces
      if (std::is_same<T,string>::value) {
        T value;
        for (auto& x_ : line) {
          value += x_;
        }
        x.push_back(value); 
      // Otherwise convert to a value
      } else {
        std::istringstream iss(line);
        T value;
        iss >> value;
        x.push_back(value);
      }      
    }
  }
  file.close();
  return true;
}

// Instantiate templates for the different types
template bool utils::readCSVFile(string, vector<vector<int64_t>> &);
template bool utils::readCSVFile(string, vector<vector<int>> &);
template bool utils::readCSVFile(string, vector<vector<string>> &);

template <typename T>
bool utils::readCSVFile(string fileName, vector<vector<T>> &output)
{
  std::ifstream file(fileName);
  if (!file)
  {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    std::exit(-1);
  }
  string row, instruction;
  while (std::getline(file, row))
  {
    vector<T> split_string;
    utils::splitString(row, ',',split_string);
    output.push_back(split_string);
  }
  file.close();
  return true;
}

// Instantiate templates for the different types
template void utils::splitString(string, char, vector<int> &);
template void utils::splitString(string, char, vector<int64_t> &);
template void utils::splitString(string, char, vector<string> &);

template <typename T>
void utils::splitString(string str, char delim,vector<T> &split)
{
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != string::npos)
  {
    end = str.find(delim, start);
    // If the template is a string, we need to preserve the whitespaces
    if (std::is_same<T, string>::value) {
      T value;
      for (auto &x_ : str.substr(start, end - start)) {
        value += x_;
      }
      split.push_back(value);
    // Otherwise, convert to a value
    } else {
      std::istringstream iss(str.substr(start, end - start));
      T value;
      iss >> value;
      split.push_back(value);
    }
  }
}