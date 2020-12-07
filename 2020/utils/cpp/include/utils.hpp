#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

/**
 * @brief Split a string with delimiter
 *
 * @param str
 * @param delim
 * @return std::vector<std::string>
 */
template <typename T>
void splitString(std::string str, char delim, std::vector<T> &split) {
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
    end = str.find(delim, start);
    // If the template is a string, we need to preserve the whitespaces
    if (std::is_same<T, std::string>::value) {
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

/**
 * @brief Read lines of a file
 *
 */
std::vector<std::string> readFile(std::string file_name) {
  std::ifstream file(file_name);
  if (!file) {
    std::cerr << "Cannot open the File : " << file_name << std::endl;
    std::exit(-1);
  }
  std::string line;
  std::vector<std::string> x;
  while (std::getline(file, line)) {
    x.push_back(line);
  }
  file.close();
  return x;
}

}  // namespace utils

#endif