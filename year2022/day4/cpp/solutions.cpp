#include "year2022/day4/cpp/solutions.hpp"

#include <array>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day4 {

using namespace std;
using input_type = vector<array<size_t, 4>>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto &row : utils::split_string<string>(input_string, "\n")) {
        array<size_t, 4U> nrs{};
        size_t count{0U};
        for (auto &x : utils::split_string<string>(row, ",")) {
            auto numbers = utils::split_string<size_t>(x, "-");
            nrs.at(count++) = numbers.at(0U);
            nrs.at(count++) = numbers.at(1U);
        }
        // Set the larger range as the first two elements
        output.push_back(
            (nrs[1] - nrs[0] > nrs[3] - nrs[2])
                ? nrs
                : array<size_t, 4U>{nrs[2], nrs[3], nrs[0], nrs[1]});
    }
    return output;
}

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    auto intersection = [](size_t lhs, array<size_t, 4U> x) {
        auto &[l1, r1, l2, r2] = x;
        return (l1 <= l2 && r1 >= r2) ? lhs + 1U : lhs;
    };
    return to_string(accumulate(input.begin(), input.end(), 0U, intersection));
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    auto intersection = [](size_t lhs, array<size_t, 4U> x) {
        auto &[l1, r1, l2, r2] = x;
        return ((l1 <= l2 && r1 >= l2) || (l1 <= r2 && r1 >= r2)) ? lhs + 1U
                                                                  : lhs;
    };
    return to_string(accumulate(input.begin(), input.end(), 0U, intersection));
}

}  // namespace day4

}  // namespace year2022
