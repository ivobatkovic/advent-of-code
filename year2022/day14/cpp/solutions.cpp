#include "year2022/day14/cpp/solutions.hpp"

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day14 {

using namespace std;
using input_type = map<pair<int, int>, int>;

static input_type transform_input(const string &input_string) {
    input_type mp{};

    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto coordinates = utils::regex_find_all<int>(row, regex{"\\d+"});

        for (size_t i{0U}; i < coordinates.size() / 2 - 1U; ++i) {
            int x1 = coordinates[2 * i];
            int y1 = coordinates[2 * i + 1];

            int x2 = coordinates[2 * i + 2];
            int y2 = coordinates[2 * i + 3];

            int dx = (x2 - x1 >= 0) ? 1 : -1;
            int dy = (y2 - y1 >= 0) ? 1 : -1;

            auto xk = x1;
            mp[{y1, xk}] = 1;
            while (xk != x2) {
                xk += dx;
                mp[{y1, xk}] = 1;
            }

            auto yk = y1;
            mp[{yk, x1}] = 1;
            while (yk != y2) {
                yk += dy;
                mp[{yk, x1}] = 1;
            }
        }
    }
    return mp;
}

string solve_part1(const string &input_string) {
    auto mp = transform_input(input_string);

    auto max_y = max_element(mp.begin(), mp.end(), [](auto i, auto j) {
                     return i.first < j.first;
                 })->first.first;

    int n_sand{0U};
    while (true) {
        int sy = 0;
        int sx = 500;
        while (true) {
            if (mp.count({sy + 1, sx})) {
                if (!mp.count({sy + 1, sx - 1})) {
                    sy++;
                    sx--;
                } else if (!mp.count({sy + 1, sx + 1})) {
                    sy++;
                    sx++;
                } else {
                    mp[{sy, sx}] = 2;
                    break;
                }
            } else {
                sy++;
            }
            if (sy >= max_y) {
                break;
            }
        }
        if (sy < max_y) {
            n_sand++;
        } else {
            break;
        }
    }

    return to_string(n_sand);
}

string solve_part2(const string &input_string) {
    auto mp = transform_input(input_string);

    auto max_y = max_element(mp.begin(), mp.end(),
                             [](auto i, auto j) { return i.first < j.first; })
                     ->first.first +
                 2;
    int n_sand{1U};
    while (true) {
        int sy = 0;
        int sx = 500;
        while (true) {
            if (mp.count({sy + 1, sx}) || sy + 1 == max_y) {
                if (!mp.count({sy + 1, sx - 1}) && sy + 1 < max_y) {
                    sy++;
                    sx--;
                } else if (!mp.count({sy + 1, sx + 1}) && sy + 1 < max_y) {
                    sy++;
                    sx++;
                } else {
                    mp[{sy, sx}] = 2;
                    break;
                }
            } else {
                sy++;
            }
        }
        if (sy == 0 && sx == 500) {
            break;
        }
        n_sand++;
    }
    return to_string(n_sand);
}

}  // namespace day14

}  // namespace year2022
