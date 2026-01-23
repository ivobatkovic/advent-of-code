#include "year2018/day6/cpp/solutions.hpp"

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2018 {

namespace day6 {

using namespace std;
using point_type = pair<int32_t, int32_t>;
using input_type = vector<point_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const numbers = utils::split_string<int32_t>(line, ", ");
        assert(numbers.size() == 2U);
        output.push_back({numbers.front(), numbers.back()});
    }
    return output;
}

int32_t manhattan(point_type const a, point_type const b) noexcept {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

array<int32_t, 4U> get_bounding_box(input_type const &points) {
    int32_t min_x = points[0].first, max_x = points[0].first;
    int32_t min_y = points[0].second, max_y = points[0].second;
    for (auto const &[x, y] : points) {
        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y);
        max_y = std::max(max_y, y);
    }
    return {min_x, max_x, min_y, max_y};
}

tuple<bool, point_type> get_closest_position(point_type const pos,
                                             input_type const &points) {
    int32_t min_distance{INT32_MAX};

    bool unique_closest_position{false};
    point_type closest_position{};

    for (auto const &point : points) {
        int32_t const distance = manhattan(pos, point);
        if (distance < min_distance) {
            closest_position = point;
            unique_closest_position = true;
            min_distance = distance;
        } else if (distance == min_distance) {
            unique_closest_position = false;
        }
    }

    return {unique_closest_position, closest_position};
}

std::string solve_part1(const string &input_string) {
    auto points = transform_input(input_string);

    auto const &[min_x, max_x, min_y, max_y] = get_bounding_box(points);

    unordered_map<point_type, size_t> count{};

    for (int32_t x{min_x}; x <= max_x; ++x) {
        for (int32_t y{min_y}; y <= max_y; ++y) {
            auto const &[unique, pos] = get_closest_position({x, y}, points);

            if (unique) {
                count[pos]++;
            }
        }
    }

    return to_string(std::max_element(count.begin(), count.end(),
                                      [](auto const &a, auto const &b) {
                                          return a.second < b.second;
                                      })
                         ->second);
}

std::string solve_part2(const string &input_string, int32_t const distance) {
    auto points = transform_input(input_string);

    auto const &[min_x, max_x, min_y, max_y] = get_bounding_box(points);

    size_t output{};
    for (int32_t x{min_x}; x <= max_x; ++x) {
        for (int32_t y{min_y}; y <= max_y; ++y) {
            int32_t const tot_distance = std::accumulate(
                points.begin(), points.end(), 0,
                [x, y](int32_t const acc, point_type const pos) {
                    return acc + manhattan({x, y}, pos);
                });
            output += (tot_distance <= distance);
        }
    }

    return to_string(output);
}

}  // namespace day6

}  // namespace year2018
