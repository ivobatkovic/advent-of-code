#include "year2022/day18/cpp/solutions.hpp"

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day18 {

using namespace std;
using input_type = set<array<int, 3>>;

static input_type transform_input(const string &input_string) {
    input_type coords{};
    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto coordinate = utils::regex_find_all<int>(row, std::regex{"\\d+"});
        coords.insert({coordinate[0], coordinate[1], coordinate[2]});
    }
    return coords;
}

std::string solve_part1(const string &input_string) {
    auto const coords = transform_input(input_string);
    vector<array<int, 3>> neighbors{{-1, 0, 0}, {1, 0, 0},  {0, -1, 0},
                                    {0, 1, 0},  {0, 0, -1}, {0, 0, 1}};

    size_t free_sides = 0;
    for (auto const &[x, y, z] : coords) {
        for (auto const &[dx, dy, dz] : neighbors) {
            if (!coords.count({x + dx, y + dy, z + dz})) {
                free_sides++;
            }
        }
    }
    return to_string(free_sides);
}

array<int, 2> get_ranges(input_type coords, size_t index) {
    auto comp = [index](auto &lhs, auto &rhs) {
        return lhs[index] < rhs[index];
    };
    return {(*min_element(begin(coords), end(coords), comp))[index] - 1,
            (*max_element(begin(coords), end(coords), comp))[index] + 1};
}

std::string solve_part2(const string &input_string) {
    auto coords = transform_input(input_string);
    vector<array<int, 3>> neighbors{{-1, 0, 0}, {1, 0, 0},  {0, -1, 0},
                                    {0, 1, 0},  {0, 0, -1}, {0, 0, 1}};

    auto [min_x, max_x] = get_ranges(coords, 0U);
    auto [min_y, max_y] = get_ranges(coords, 1U);
    auto [min_z, max_z] = get_ranges(coords, 2U);

    queue<array<int, 3>> q;
    q.push({0, 0, 0});

    size_t free_sides{0U};
    set<array<int, 3>> visited{};
    visited.insert({0, 0, 0});
    while (!q.empty()) {
        auto &[x, y, z] = q.front();
        q.pop();
        for (auto &[dx, dy, dz] : neighbors) {
            array<int, 3> coord{x + dx, y + dy, z + dz};
            if (!visited.count(coord)) {
                if (coords.count(coord)) {
                    free_sides++;
                } else if (min_x <= coord[0] && coord[0] <= max_x &&
                           min_y <= coord[1] && coord[1] <= max_y &&
                           min_z <= coord[2] && coord[2] <= max_z) {
                    visited.insert(coord);
                    q.push(coord);
                }
            }
        }
    }

    return to_string(free_sides);
}

}  // namespace day18

}  // namespace year2022
