#include "utils/cpp_utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

void push_transform(std::string str, std::vector<std::string> &split) {
    split.push_back(str);
}

std::string read_file_to_string(std::string file_name) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Cannot open file " << file_name << std::endl;
        std::exit(-1);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    return (content.back() == '\n') ? content.substr(0U, content.size() - 1U)
                                    : content;
}

}  // namespace utils
