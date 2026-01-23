#include "year2024/day6/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

struct ArrayHash {
    std::size_t operator()(const std::array<int32_t, 4> &a) const noexcept {
        std::size_t h = 0;
        for (int32_t v : a) {
            h ^= std::hash<int32_t>{}(v) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};

namespace year2024 {

namespace day6 {

using namespace std;
using pos_type = pair<int32_t, int32_t>;
using grid_type = unordered_map<pos_type, char>;
using input_type = tuple<pos_type, grid_type, int32_t, int32_t>;

static input_type transform_input(const string &input_string) {
    grid_type grid{};
    pos_type start_pos{};

    auto const rows = utils::split_string<string>(input_string, "\n");
    for (size_t i{0U}; i < rows.size(); ++i) {
        for (size_t j{0U}; j < rows.at(i).size(); ++j) {
            const char chr = rows.at(i).at(j);
            grid[{i, j}] = chr;

            if (chr == '^') {
                start_pos = {i, j};
            }
        }
    }
    return {start_pos, grid, rows.size(), rows.at(0U).size()};
}

bool traverse(pos_type pos, grid_type &grid, int32_t const num_rows,
              int32_t const num_cols, bool const part_two = false) {
    array<pos_type, 4U> directions{make_pair(0, -1), make_pair(1, 0),
                                   make_pair(0, 1), make_pair(-1, 0)};

    auto [dx, dy] = directions.at(0U);
    size_t i{0U};

    unordered_set<array<int32_t, 4U>, ArrayHash> visited;

    while (0 <= pos.first && pos.first < num_rows && 0 <= pos.second &&
           pos.second < num_cols) {
        array<int32_t, 4U> state{pos.first, pos.second, dx, dy};
        if (part_two && visited.contains(state)) {
            return false;
        }
        visited.insert(state);

        pos_type new_pos{pos.first + dy, pos.second + dx};

        if (grid[new_pos] == '#') {
            i = (i + 1U) % 4U;
            std::tie(dx, dy) = directions.at(i);
            ;
        } else {
            grid[pos] = 'X';
            pos = new_pos;
        }
    }
    return true;
}

std::string solve_part1(const string &input_string) {
    auto [pos, grid, num_rows, num_cols] = transform_input(input_string);

    traverse(pos, grid, num_rows, num_cols);

    return to_string(accumulate(grid.begin(), grid.end(), 0,
                                [](int32_t acc, auto const pair) {
                                    return acc + (pair.second == 'X');
                                }));
}

std::string solve_part2(const string &input_string) {
    auto [pos, grid, num_rows, num_cols] = transform_input(input_string);

    traverse(pos, grid, num_rows, num_cols);

    size_t output{};

    vector<pos_type> positions{};
    for (auto &[key, value] : grid) {
        if (value == 'X') {
            positions.push_back(key);
        }
    }

    for (auto const &key : positions) {
        grid[key] = '#';
        if (!traverse(pos, grid, num_rows, num_cols, true)) {
            output++;
        }
        grid[key] = 'X';
    }
    return to_string(output);
}

}  // namespace day6

}  // namespace year2024
