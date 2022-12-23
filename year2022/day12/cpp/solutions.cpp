#include "year2022/day12/cpp/solutions.hpp"

#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day12 {

using pair_type = std::pair<size_t, size_t>;
using input_type = std::pair<std::vector<std::string>, pair_type>;
using q_type = std::tuple<pair_type, char, size_t>;

static input_type transform_input(const std::string &input_string) {
    auto rows = utils::split_string<std::string>(input_string, "\n");

    pair_type end{};
    for (size_t row{0U}; row < rows.size(); ++row) {
        for (size_t col{0U}; col < rows[row].size(); ++col) {
            if (rows[row][col] == 'E') {
                end = std::make_pair(row, col);
                break;
            }
        }
    }
    return std::make_pair(rows, end);
}

std::string traverse(std::vector<std::string> const &inp,
                     pair_type const &start, char const goal,
                     char const elevation = 'z') {
    std::map<std::pair<int, int>, size_t> visited{};
    std::deque<q_type> q = {std::make_tuple(start, elevation, 0U)};

    while (q.size() != 0) {
        auto [pos, val, dist] = q.front();
        q.pop_front();

        if (val == goal) {
            return std::to_string(dist);
        }

        if (visited.count(pos)) {
            continue;
        }

        visited[pos] = dist;
        auto &[row, col] = pos;

        std::vector<std::array<int, 2>> directions = {
            {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (auto [drow, dcol] : directions) {
            int r_ = static_cast<int>(row) + drow;
            int c_ = static_cast<int>(col) + dcol;
            if (0 <= r_ && r_ < static_cast<int>(inp.size()) && 0 <= c_ &&
                c_ < static_cast<int>(inp.at(0U).size())) {
                size_t r_t = static_cast<size_t>(r_);
                size_t c_t = static_cast<size_t>(c_);
                auto next_val = (inp[r_t][c_t] == 'S') ? 'a' : inp[r_t][c_t];
                if (val - next_val <= 1) {
                    q.push_back(std::make_tuple(std::make_pair(r_t, c_t),
                                                inp[r_t][c_t], dist + 1U));
                }
            }
        }
    }
    return "";
}

std::string solve_part1(const std::string &input_string) {
    auto [input, end] = transform_input(input_string);
    return traverse(input, end, 'S');
}

std::string solve_part2(const std::string &input_string) {
    auto [input, end] = transform_input(input_string);
    return traverse(input, end, 'a');
}

}  // namespace day12

}  // namespace year2022
