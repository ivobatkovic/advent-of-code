#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

std::vector<std::string> read_file(std::string file_name);

template <typename T>
void push_transform(std::string str, std::vector<T> &split) {
  // If the template is a string, we need to preserve the whitespaces
  if (std::is_same<T, std::string>::value) {
    T value;
    for (auto &x_ : str) {
      value += x_;
    }
    split.push_back(value);
    // Otherwise, convert to a value
  } else {
    std::istringstream iss(str);
    T value;
    iss >> value;
    split.push_back(value);
  }
}

/**
 * @brief Split a string with delimiter
 *
 * @param str
 * @param delim
 * @return std::vector<std::string>
 */
template <typename T>
void split_string(std::string str, std::string delim, std::vector<T> &split) {
  size_t pos;
  while ((pos = str.find(delim)) != std::string::npos) {
    push_transform(str.substr(0, pos), split);
    str.erase(0, pos + delim.length());
  }
  push_transform(str, split);
}
template <typename T>
void split_string(std::string str, char delim, std::vector<T> &split) {
  split_string(str, std::string(1, delim), split);
}

/**
 * @brief Read lines of a file
 *
 */
std::vector<std::string> read_file(std::string file_name) {
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