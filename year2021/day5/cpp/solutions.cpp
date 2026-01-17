#include "year2021/day5/cpp/solutions.hpp"

#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2021 {

namespace day5 {

using namespace std;
using input_type = vector<array<int32_t, 4U>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const numbers =
            utils::regex_find_all<int32_t>(line, boost::regex("\\d+"));
        output.push_back(
            {numbers.at(0U), numbers.at(1U), numbers.at(2U), numbers.at(3U)});
    }
    return output;
}

int32_t sign(int32_t const x1, int32_t const x2) {
    return (x2 > x1) - (x1 > x2);
}

size_t solve(input_type &input, bool const diagonals = false) {
    unordered_map<pair<int32_t, int32_t>, size_t> grid{};

    for (auto &[x1, y1, x2, y2] : input) {
        int32_t dx = sign(x1, x2);
        int32_t dy = sign(y1, y2);

        if (!diagonals && dx != 0 && dy != 0) {
            continue;
        }

        grid[{x1, y1}]++;

        while (x1 != x2 || y1 != y2) {
            x1 += dx;
            y1 += dy;
            grid[{x1, y1}]++;
        }
    }

    size_t output{};
    for (auto const &[key, value] : grid) {
        output += (value > 1) ? 1U : 0U;
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(solve(input));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(solve(input, true));
}

}  // namespace day5

}  // namespace year2021
