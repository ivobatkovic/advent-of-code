#include "year2022/day25/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day25 {

using namespace std;
using input_type = vector<string>;

namespace constants {
const string base = "=-012";
const map<char, int> offset{{'=', 0}, {'-', 1}, {'0', 2}, {'1', 3}, {'2', 4}};
}  // namespace constants

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

int64_t to_decimal(string const &snafu) {
    if (snafu.size() > 0) {
        return to_decimal(snafu.substr(0, snafu.size() - 1)) * 5 +
               constants::offset.at(snafu.back()) - 2;
    } else {
        return 0;
    }
}

string to_snafu(int64_t const decimal) {
    if (decimal) {
        auto divmod = div(decimal + 2L, 5L);
        return to_snafu(divmod.quot) +
               constants::base.at(static_cast<size_t>(divmod.rem));
    }
    return "";
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    int64_t value = 0;
    for (auto &x : input) {
        value += to_decimal(x);
    }
    return to_snafu(value);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return "Implement part two";
}

}  // namespace day25

}  // namespace year2022
