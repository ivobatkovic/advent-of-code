#include "include/cpp_utils.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace utils {

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

std::string read_file_to_string(std::string file_name) {
  std::ifstream file(file_name);
  if (!file) {
    std::cerr << "Cannot open the File : " << file_name << std::endl;
    std::exit(-1);
  }
  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

}
