#include "year2022/day2/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day2 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    const unordered_map<string, size_t> rule_book{
        {"A X", 1U + 3U}, {"A Y", 2U + 6U}, {"A Z", 3U + 0U},
        {"B X", 1U + 0U}, {"B Y", 2U + 3U}, {"B Z", 3U + 6U},
        {"C X", 1U + 6U}, {"C Y", 2U + 0U}, {"C Z", 3U + 3U},
    };

    auto x = [&rule_book](size_t lhs, string rhs) {
        return lhs + rule_book.at(rhs);
    };
    return to_string(accumulate(input.begin(), input.end(), 0U, x));
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    const unordered_map<string, size_t> rule_book{
        {"A X", 3U + 0U}, {"A Y", 1U + 3U}, {"A Z", 2U + 6U},
        {"B X", 1U + 0U}, {"B Y", 2U + 3U}, {"B Z", 3U + 6U},
        {"C X", 2U + 0U}, {"C Y", 3U + 3U}, {"C Z", 1U + 6U},
    };

    auto x = [&rule_book](size_t lhs, string rhs) {
        return lhs + rule_book.at(rhs);
    };
    return to_string(accumulate(input.begin(), input.end(), 0U, x));
}

}  // namespace day2

}  // namespace year2022
