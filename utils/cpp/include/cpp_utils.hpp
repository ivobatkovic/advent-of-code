#ifndef _CPP_UTILS_H_
#define _CPP_UTILS_H_

#include <sstream>
#include <string>
#include <vector>

namespace utils {

/// Template function to push_back a generic value
///
/// @param str String value to push_back
/// @tparam[out] split Template vector holding the values
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

/// Split a string using a string delimiter
///
/// @param str Input string
/// @param delim Delimiter string
/// @tparam[out] split Template vector containing all sub-strings
template <typename T>
std::vector<T> split_string(std::string str, std::string delim) {
    std::vector<T> split;
    size_t pos;
    while ((pos = str.find(delim)) != std::string::npos) {
        push_transform(str.substr(0, pos), split);
        str.erase(0, pos + delim.length());
    }
    push_transform(str, split);
    return split;
}

/// Split a string using a character delimiter
///
/// @param str Input string
/// @param delim Delimiter character
/// @tparam[out] split Template vector containing all sub-strings
template <typename T>
std::vector<T> split_string(std::string str, char delim) {
    return split_string<T>(str, std::string(1, delim));
}

/// Read contents of a file
///
/// @param file_name Name of the file
/// @return Vector with strings representing each row of the file
std::vector<std::string> read_file(std::string file_name);

/// Read file contents into a string
///
/// @param file_name Name of the file
/// @return A string containing the entire file content
std::string read_file_to_string(std::string file_name);

}  // namespace utils

#endif