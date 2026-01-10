#include "year2018/day5/cpp/solutions.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace year2018 {

namespace day5 {

using namespace std;
using input_type = vector<char>;

static input_type transform_input(const string &input_string) {
    return {input_string.begin(), input_string.end()};
}

size_t collapse(input_type const &polymer) {
    input_type stack{};

    for (auto const &chr : polymer) {
        if (!stack.empty() && abs(stack.back() - chr) == 32) {
            stack.pop_back();
        } else {
            stack.push_back(chr);
        }
    }
    return stack.size();
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(collapse(input));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t min_length = input.size();
    for (int32_t i = 'a'; i < 'z' + 1; ++i) {
        vector<char> polymer{};
        std::copy_if(input.begin(), input.end(), std::back_inserter(polymer),
                     [i](char x) {
                         char lower = (x >= 'A' && x <= 'Z') ? x + 32 : x;
                         return lower != i;
                     });
        min_length = std::min(min_length, collapse(polymer));
    }

    return to_string(min_length);
}

}  // namespace day5

}  // namespace year2018
