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

using input_type = std::vector<std::array<size_t, 4>>;

static input_type transform_input(const std::string &input_string) {
    input_type output{};
    for (auto &row : utils::split_string<std::string>(input_string, "\n")) {
        std::array<size_t, 4U> nrs{};
        size_t count{0U};
        for (auto &x : utils::split_string<std::string>(row, ",")) {
            auto numbers = utils::split_string<size_t>(x, "-");
            nrs.at(count++) = numbers.at(0U);
            nrs.at(count++) = numbers.at(1U);
        }
        // Set the larger range as the first two elements
        output.push_back(
            (nrs[1] - nrs[0] > nrs[3] - nrs[2])
                ? nrs
                : std::array<size_t, 4U>{nrs[2], nrs[3], nrs[0], nrs[1]});
    }
    return output;
    asda
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    auto intersection = [](size_t lhs, std::array<size_t, 4U> x) {
        auto &[l1, r1, l2, r2] = x;
        return (l1 <= l2 && r1 >= r2) ? lhs + 1U : lhs;
    };
    return std::to_string(
        std::accumulate(input.begin(), input.end(), 0U, intersection));
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    auto intersection = [](size_t lhs, std::array<size_t, 4U> x) {
        auto &[l1, r1, l2, r2] = x;
        return ((l1 <= l2 && r1 >= l2) || (l1 <= r2 && r1 >= r2)) ? lhs + 1U
                                                                  : lhs;
    };
    return std::to_string(
        std::accumulate(input.begin(), input.end(), 0U, intersection));
}

}  // namespace day4

}  // namespace year2022
