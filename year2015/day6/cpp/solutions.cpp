#include "year2015/day6/cpp/solutions.hpp"

#include <array>
#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2015 {

namespace day6 {

using namespace std;

using numbers_type = array<size_t, 4U>;
using input_type = vector<pair<string, numbers_type>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const action = utils::regex_find_all<string>(
            line, boost::regex("(on|off|toggle)"));
        assert(action.size() == 2U);
        auto const numbers =
            utils::regex_find_all<size_t>(line, boost::regex("\\d+"));
        assert(numbers.size() == 4U);

        numbers_type numbers_array{};
        copy(numbers.begin(), numbers.end(), numbers_array.begin());

        output.push_back(make_pair(action.back(), numbers_array));
    }
    return output;
}

template <typename Op>
string process_grid(const input_type &input, Op op) {
    array<array<int32_t, 1000U>, 1000U> grid{};

    for (auto const &[action, numbers] : input) {
        auto [x0, y0, x1, y1] = numbers;
        for (size_t x{x0}; x <= x1; ++x) {
            for (size_t y{y0}; y <= y1; ++y) {
                op(grid[x][y], action);
            }
        }
    }

    int32_t total{};
    for (auto const &row : grid) {
        total += accumulate(row.begin(), row.end(), int32_t{});
    }
    return to_string(total);
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return process_grid(input, [](int32_t &cell, const string &action) {
        if (action == "on") {
            cell = 1;
        } else if (action == "off") {
            cell = 0;
        } else {
            cell = 1 - cell;
        };
    });
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    return process_grid(input, [](int32_t &cell, const string &action) {
        if (action == "on") {
            cell++;
        } else if (action == "off") {
            cell = max(0, cell - 1);
        } else {
            cell += 2;
        };
    });
}

}  // namespace day6

}  // namespace year2015
