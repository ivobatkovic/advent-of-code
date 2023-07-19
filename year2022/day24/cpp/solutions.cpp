#include "year2022/day24/cpp/solutions.hpp"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day24 {

using namespace std;
using set_t = set<pair<int, int>>;
using blizzard_t = set<tuple<int, int, int, int>>;
using input_type = tuple<set_t, blizzard_t, int, int>;

static input_type transform_input(const string& input_string) {
    auto rows = utils::split_string<string>(input_string, "\n");

    // Inner grid sizes
    size_t height = rows.size() - 2;
    size_t width = rows.at(0U).size() - 2;

    // Make inner grid top left corner to be (0,0) instead of (1,1)
    set_t grid{};
    blizzard_t blizzards{};
    for (size_t y{0U}; y < rows.size(); ++y) {
        for (size_t x{0U}; x < rows.at(0U).size(); ++x) {
            char chr{rows.at(y).at(x)};
            int y_ = static_cast<int>(y);
            int x_ = static_cast<int>(x);
            if (chr == '#') grid.insert({y_ - 1, x_ - 1});
            if (chr == '>') blizzards.insert({y_ - 1, x_ - 1, 0, 1});
            if (chr == '<') blizzards.insert({y_ - 1, x_ - 1, 0, -1});
            if (chr == 'v') blizzards.insert({y_ - 1, x_ - 1, 1, 0});
            if (chr == '^') blizzards.insert({y_ - 1, x_ - 1, -1, 0});
        }
    }

    // Pad start and exit
    grid.insert({-2, 0});
    grid.insert({static_cast<int>(height) + 1, static_cast<int>(width) - 1});

    return make_tuple(grid, blizzards, height, width);
}

string traverse_grid(set_t const& grid, blizzard_t const& blizzards, int height,
                     int width, pair<int, int> const& start,
                     vector<pair<int, int>> checkpoints) {
    int t = 0;
    set_t q;
    q.insert(start);

    std::array<pair<int, int>, 5U> directions{make_pair(1, 0), make_pair(-1, 0),
                                              make_pair(0, 1), make_pair(0, -1),
                                              make_pair(0, 0)};

    while (checkpoints.size() != 0U) {
        t++;

        set_t blizzard_pos;
        for (auto& [py, px, dy, dx] : blizzards) {
            int y_ = (py + t * dy) % height;
            int x_ = (px + t * dx) % width;

            y_ = (y_ < 0) ? height + y_ : y_;
            x_ = (x_ < 0) ? width + x_ : x_;
            blizzard_pos.insert({y_, x_});
        }

        set_t new_positions;
        for (auto& [py, px] : q) {
            for (auto& [dy, dx] : directions) {
                new_positions.insert({py + dy, px + dx});
            }
        }
        q = new_positions;

        for (auto& pos : blizzard_pos) {
            if (q.count(pos)) {
                q.erase(pos);
            }
        }
        for (auto& pos : grid) {
            if (q.count(pos)) {
                q.erase(pos);
            }
        }

        if (q.count(checkpoints.at(0U))) {
            q = set<pair<int, int>>{checkpoints.at(0U)};
            checkpoints.erase(checkpoints.begin());
        }
    }
    return to_string(t);
}

std::string solve_part1(const string& input_string) {
    auto [grid, blizzards, height, width] = transform_input(input_string);
    auto start = pair<int, int>(-1, 0);
    auto end = pair<int, int>(height, width - 1);
    return traverse_grid(grid, blizzards, height, width, start, {end});
}

std::string solve_part2(const string& input_string) {
    auto [grid, blizzards, height, width] = transform_input(input_string);
    auto start = pair<int, int>(-1, 0);
    auto end = pair<int, int>(height, width - 1);
    return traverse_grid(grid, blizzards, height, width, start,
                         {end, start, end});
}

}  // namespace day24

}  // namespace year2022
