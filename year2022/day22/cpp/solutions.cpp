#include "year2022/day22/cpp/solutions.hpp"

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day22 {

using namespace std;

using map_t = map<pair<int64_t, int64_t>, char>;
using instruction_t = vector<string>;

using input_type = pair<map_t, instruction_t>;

static input_type transform_input(const string &input_string) {
    map_t grid;
    auto rows = utils::split_string<string>(input_string, "\n");

    for (size_t y = 0; y < rows.size() - 2U; ++y) {
        for (size_t x = 0; x < rows.at(y).size(); x++) {
            char chr = rows.at(y).at(x);
            if (chr == '.' || chr == '#') {
                grid[make_pair(y, x)] = chr;
            }
        }
    }
    auto instructions =
        utils::regex_find_all<string>(rows.back(), regex("\\d+|R|L"));
    return {grid, instructions};
}

array<int64_t, 3U> wrap_part1(map_t const &grid, int64_t y, int64_t x,
                              int64_t direction) {
    if (direction == 0 || direction == 2) {
        vector<int64_t> x_values{};
        for (auto xx : grid) {
            if (xx.first.first == y) {
                x_values.push_back(xx.first.second);
            }
        }
        return (direction == 0)
                   ? array<int64_t, 3U>{y,
                                        *min_element(x_values.begin(),
                                                     x_values.end()),
                                        direction}
                   : array<int64_t, 3U>{
                         y, *max_element(x_values.begin(), x_values.end()),
                         direction};
    } else if (direction == 1 || direction == 3) {
        vector<int64_t> y_values{};
        for (auto xx : grid) {
            if (xx.first.second == x) {
                y_values.push_back(xx.first.first);
            }
        }
        return (direction == 1)
                   ? array<int64_t, 3U>{*min_element(y_values.begin(),
                                                     y_values.end()),
                                        x, direction}
                   : array<int64_t, 3U>{
                         *max_element(y_values.begin(), y_values.end()), x,
                         direction};
    } else {
        return {y, x, direction};
    }
}

array<int64_t, 3U> wrap_part2(int64_t y, int64_t x, int64_t direction) {
    auto y_ = y / 50;
    auto x_ = x / 50;
    if (direction == 0 and y_ == 0)
        return {149 - y, 99, 2};
    else if (direction == 0 and y_ == 1)
        return {49, y + 50, 3};
    else if (direction == 0 and y_ == 2)
        return {149 - y, 149, 2};
    else if (direction == 0 and y_ == 3)
        return {149, y - 100, 3};
    else if (direction == 2 and y_ == 0)
        return {149 - y, 0, 0};
    else if (direction == 2 and y_ == 1)
        return {100, y - 50, 1};
    else if (direction == 2 and y_ == 2)
        return {149 - y, 50, 0};
    else if (direction == 2 and y_ == 3)
        return {0, y - 100, 1};
    else if (direction == 1 and x_ == 0)
        return {0, x + 100, 1};
    else if (direction == 1 and x_ == 1)
        return {100 + x, 49, 2};
    else if (direction == 1 and x_ == 2)
        return {-50 + x, 99, 2};
    else if (direction == 3 and x_ == 0)
        return {50 + x, 50, 0};
    else if (direction == 3 and x_ == 1)
        return {100 + x, 0, 0};
    else
        return {199, x - 100, 3};
}

int64_t traverse_map(map_t const &grid, instruction_t const &instructions,
                     bool part1 = true) {
    // Find start position at the top row
    int64_t sy = 0;
    int64_t sx = 0;
    while (true) {
        if (grid.count({sy, sx}) && grid.at({sy, sx}) == '.') {
            break;
        }
        sx++;
    }

    array<pair<int8_t, int8_t>, 4U> directions = {
        make_pair(0, 1), make_pair(1, 0), make_pair(0, -1), make_pair(-1, 0)};
    int64_t direction = 0;

    for (const auto &instr : instructions) {
        if (instr == "L") {
            direction = (direction - 1) % 4;
        } else if (instr == "R") {
            direction = (direction + 1) % 4;
        } else {
            direction = (direction < 0) ? direction + 4 : direction;
            for (int32_t i = 0; i < stoi(instr); ++i) {
                int64_t py =
                    sy + directions.at(static_cast<size_t>(direction)).first;
                int64_t px =
                    sx + directions.at(static_cast<size_t>(direction)).second;
                int64_t d = direction;
                if (!grid.count({py, px})) {
                    auto [py_, px_, d_] =
                        (part1) ? wrap_part1(grid, py, px, direction)
                                : wrap_part2(py, px, direction);
                    py = py_;
                    px = px_;
                    d = d_;
                }
                if (grid.at({py, px}) == '.') {
                    sy = py;
                    sx = px;
                    direction = d;
                } else {
                    break;
                }
            }
        }
    }
    return 1000 * (sy + 1) + 4 * (sx + 1) + direction;
}

std::string solve_part1(const string &input_string) {
    auto [grid, instructions] = transform_input(input_string);
    return to_string(traverse_map(grid, instructions));
}

std::string solve_part2(const string &input_string) {
    auto [grid, instructions] = transform_input(input_string);
    return to_string(traverse_map(grid, instructions, false));
}

}  // namespace day22

}  // namespace year2022
