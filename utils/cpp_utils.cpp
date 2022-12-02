#include "utils/cpp_utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

std::vector<std::string> read_file(std::string file_name) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Cannot open file : " << file_name << std::endl;
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
        std::cerr << "Cannot open file " << file_name << std::endl;
        std::exit(-1);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string file_content = ss.str();
    return file_content.substr(0, file_content.size() - 1);
}

}  // namespace utils
