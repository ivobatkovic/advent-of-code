#include "year2022/day6/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day6 {

using input_type = std::string;

static input_type transform_input(const std::string &input_string) {
    return input_string;
}

size_t find_marker(std::string const &message, size_t length = 4) {
    std::unordered_map<char, size_t> d;
    size_t left{0U};
    for (size_t right{0U}; right < message.length(); ++right) {
        d[message[right]]++;

        if (d[message[right]] > 1) {
            while (true) {
                d[message[left]]--;
                left++;
                if (d[message[left - 1U]] == d[message[right]]) {
                    break;
                }
            }
        } else if (right + 1U - left == length) {
            return right + 1U;
        }
    }
    return message.length();
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    return std::to_string(find_marker(input));
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    return std::to_string(find_marker(input, 14));
}

}  // namespace day6

}  // namespace year2022
