#include "year2025/day3/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2025 {

namespace day3 {

using namespace std;
using input_type = vector<vector<int32_t>>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        vector<int32_t> digits(line.size());
        std::transform(line.begin(), line.end(), digits.begin(),
                       [](char c) { return c - '0'; });
        output.push_back(digits);
    }
    return output;
}

int64_t find_joltage(vector<int32_t> const &digits, int32_t const length = 2U) {
    int32_t N = static_cast<int32_t>(digits.size());
    string jolt{};
    int32_t pos = 0U;

    int32_t look_ahead = N - length;

    for (int32_t i{0U}; i < length; ++i) {
        auto it = std::max_element(digits.begin() + pos,
                                   digits.begin() + pos + look_ahead + 1);

        int32_t max_value = *it;
        int32_t index = static_cast<int32_t>(std::distance(digits.begin(), it));

        jolt += to_string(max_value);
        look_ahead -= (index - pos);
        pos = index + 1;
    }
    return stol(jolt);
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(input.begin(), input.end(), 0L,
                                [](int64_t const acc, auto const &digits) {
                                    return acc + find_joltage(digits);
                                }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(accumulate(input.begin(), input.end(), 0L,
                                [](int64_t const acc, auto const &digits) {
                                    return acc + find_joltage(digits, 12);
                                }));
}

}  // namespace day3

}  // namespace year2025
