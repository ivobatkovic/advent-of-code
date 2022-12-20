#include "year2022/day8/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day8 {

using input_type = std::vector<std::string>;
using map_type = std::map<std::pair<int, int>, size_t>;

static input_type transform_input(const std::string &input_string) {
    return utils::split_string<std::string>(input_string, "\n");
}

void compute_visibility(map_type &heights, input_type const &inp, int dx,
                        int dy) {
    if (dx) {
        for (size_t row = 0; row < inp.size(); ++row) {
            int start = (dx > 0) ? 0 : static_cast<int>(inp[row].length()) - 1;
            int val = -1;
            while ((start > -1) &&
                   (start < static_cast<int>(inp[row].size()))) {
                if (val < inp[row][static_cast<size_t>(start)]) {
                    heights[std::make_pair(row, start)] = 1;
                    val = inp[row][static_cast<size_t>(start)];
                }
                if (val == '9') {
                    break;
                }
                start += dx;
            }
        }
    } else {
        for (size_t col = 0; col < inp[0].size(); ++col) {
            int start = (dy > 0) ? 0 : static_cast<int>(inp.size()) - 1;
            int val = -1;
            while ((start > -1) && (start < static_cast<int>(inp.size()))) {
                if (val < inp[static_cast<size_t>(start)][col]) {
                    heights[std::make_pair(start, col)] = 1;
                    val = inp[static_cast<size_t>(start)][col];
                }
                if (val == '9') {
                    break;
                }
                start += dy;
            }
        }
    }
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    map_type heights{};

    std::vector<std::array<int, 2>> directions{
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    for (auto [dx, dy] : directions) {
        compute_visibility(heights, input, dx, dy);
    }

    auto point = [](auto lhs, auto &rhs) { return lhs + rhs.second; };
    return std::to_string(
        std::accumulate(heights.begin(), heights.end(), 0U, point));
}

void compute_scenic_score(map_type &heights, input_type &inp,
                          std::vector<std::array<int, 2>> const &directions,
                          size_t row, size_t col) {
    size_t total = 1;
    for (auto &[dx, dy] : directions) {
        size_t count = 1;
        if (dx) {
            int k = static_cast<int>(col) + dx;
            while ((k > 0 && k < static_cast<int>(inp[0].size()) - 1) &&
                   inp[row][col] > inp[row][static_cast<size_t>(k)]) {
                count++;
                k += dx;
            }
        } else {
            int k = static_cast<int>(row) + dy;
            while ((k > 0 && k < static_cast<int>(inp.size()) - 1) &&
                   inp[row][col] > inp[static_cast<size_t>(k)][col]) {
                count++;
                k += dy;
            }
        }
        total *= count;
    }
    heights[std::make_pair(static_cast<int>(row), static_cast<int>(col))] =
        total;
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);

    map_type heights{};
    std::vector<std::array<int, 2>> directions{
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (size_t row = 1U; row < input.size() - 1; ++row) {
        for (size_t col = 1U; col < input[0].size() - 1; ++col) {
            compute_scenic_score(heights, input, directions, row, col);
        }
    }
    auto comp = [](auto &a, auto &b) { return b.second > a.second; };
    return std::to_string(
        std::max_element(heights.begin(), heights.end(), comp)->second);
}

}  // namespace day8

}  // namespace year2022
