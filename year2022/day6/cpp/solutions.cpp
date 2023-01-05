#include "year2022/day6/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day6 {

using namespace std;
using input_type = string;

static input_type transform_input(const string &input_string) {
    return input_string;
}

size_t find_marker(string const &message, size_t length = 4) {
    unordered_map<char, size_t> d;
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

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(find_marker(input));
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(find_marker(input, 14));
}

}  // namespace day6

}  // namespace year2022
