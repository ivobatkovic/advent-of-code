#include "year2022/day15/cpp/solutions.hpp"

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day15 {

using namespace std;
using sensor_type = array<int, 3>;
using beacon_type = set<pair<int, int>>;
using input_type = pair<vector<sensor_type>, beacon_type>;

static input_type transform_input(const string &input_string) {
    vector<sensor_type> sensors;
    beacon_type beacons{};
    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto coordinates = utils::regex_find_all<int>(row, regex("-?\\d+"));
        auto x1 = coordinates[0];
        auto y1 = coordinates[1];
        auto x2 = coordinates[2];
        auto y2 = coordinates[3];
        sensors.push_back({y1, x1, abs(x2 - x1) + abs(y2 - y1)});
        beacons.insert({y2, x2});
    }
    return make_pair(sensors, beacons);
}

vector<array<int, 2>> get_intervals(vector<sensor_type> const &sensors,
                                    const int y_line) {
    vector<array<int, 2>> intervals;
    for (auto &[y, x, dist] : sensors) {
        auto dx = dist - abs(y_line - y);
        if (dx < 0) {
            continue;
        }
        intervals.push_back({x - dx, x + dx});
    }
    return intervals;
}

string solve_part1(const string &input_string, const size_t y_line) {
    auto [sensors, beacons] = transform_input(input_string);

    auto intervals = get_intervals(sensors, static_cast<int>(y_line));
    if (intervals.size() == 0) {
        return "0";
    }

    int left_interval = (*min_element(intervals.begin(), intervals.end(),
                                      [](auto const &lhs, auto const &rhs) {
                                          return lhs[0] < rhs[0];
                                      }))
                            .front();
    int right_interval = (*max_element(intervals.begin(), intervals.end(),
                                       [](auto const &lhs, auto const &rhs) {
                                           return lhs[1] < rhs[1];
                                       }))
                             .back();
    int n_locations = right_interval - left_interval + 1;
    for (auto [y, x] : beacons) {
        if (y == static_cast<int>(y_line) && x >= left_interval &&
            x <= right_interval) {
            n_locations--;
        }
    }
    return to_string(n_locations);
}

string solve_part2(const string &input_string, const size_t y_max) {
    auto [sensors, _] = transform_input(input_string);
    for (size_t y_line = 0U; y_line < y_max + 1U; ++y_line) {
        auto intervals = get_intervals(sensors, static_cast<int>(y_line));
        sort(intervals.begin(), intervals.end(),
             [](auto const &lhs, auto const &rhs) { return lhs[0] < rhs[0]; });

        vector<array<int, 2>> intersections;
        auto left = intervals.front()[0];
        auto right = intervals.front()[1];
        for (auto &[ll, rr] : intervals) {
            if (right + 1 >= ll) {
                right = max(right, rr);
            } else {
                intersections.push_back({left, right});
                left = ll;
                right = rr;
            }
        }
        intersections.push_back({left, right});

        if (intersections.size() > 1) {
            return to_string(int64_t(4000000) * (intersections[0][1] + 1) +
                             static_cast<int64_t>(y_line));
        }
    }
    return "0";
}

}  // namespace day15

}  // namespace year2022
