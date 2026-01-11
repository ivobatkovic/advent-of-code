#include "year2020/day5/cpp/solutions.hpp"

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2020 {

namespace day5 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    for (auto const &line : input) {
        pair<size_t, size_t> rows{0, 127};
        pair<size_t, size_t> cols{0, 8};

        for (const char chr : line) {
            if (chr == 'F') {
                rows.second = (rows.first + rows.second) / 2;
            } else if (chr == 'B') {
                rows.first = (rows.first + rows.second + 1) / 2;
            }
            if (chr == 'L') {
                cols.second = (cols.first + cols.second) / 2;
            } else if (chr == 'R') {
                cols.first = (cols.first + cols.second + 1) / 2;
            }
        }

        output = max(output, min(rows.first, rows.second) * 8U +
                                 min(cols.first, cols.second));
    }

    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    unordered_set<size_t> ids{};

    for (auto const &line : input) {
        pair<size_t, size_t> rows{0, 127};
        pair<size_t, size_t> cols{0, 8};

        for (const char chr : line) {
            if (chr == 'F') {
                rows.second = (rows.first + rows.second) / 2;
            } else if (chr == 'B') {
                rows.first = (rows.first + rows.second + 1) / 2;
            }
            if (chr == 'L') {
                cols.second = (cols.first + cols.second) / 2;
            } else if (chr == 'R') {
                cols.first = (cols.first + cols.second + 1) / 2;
            }
        }

        ids.insert(min(rows.first, rows.second) * 8U +
                   min(cols.first, cols.second));
    }

    for (auto const x : ids) {
        if (!ids.contains(x + 1) && ids.contains(x + 2))
            return to_string(x + 1);
    }

    return "0";
}

}  // namespace day5

}  // namespace year2020
