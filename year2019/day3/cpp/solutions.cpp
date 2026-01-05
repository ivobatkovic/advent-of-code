#include "year2019/day3/cpp/solutions.hpp"

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2019 {

namespace day3 {

using namespace std;
using segment_type = array<int32_t, 4U>;
using line_type = vector<segment_type>;
using input_type = array<line_type, 2U>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    size_t counter{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        vector<array<int32_t, 4U>> steps{};
        pair<int32_t, int32_t> pos{};
        for (string const &instruction :
             utils::split_string<string>(line, ",")) {
            char const direction = instruction.at(0U);
            int32_t step = stoi(instruction.substr(1, instruction.size()));

            int32_t dx{}, dy{};
            if (direction == 'U') {
                dy = step;
            } else if (direction == 'D') {
                dy = -step;
            } else if (direction == 'L') {
                dx = -step;
            } else if (direction == 'R') {
                dx = step;
            };

            pair<int32_t, int32_t> new_pos{pos.first + dx, pos.second + dy};

            steps.push_back(
                {pos.first, pos.second, new_pos.first, new_pos.second});
            pos = new_pos;
        }
        output.at(counter++) = steps;
    }
    return output;
}

pair<bool, pair<int32_t, int32_t>> check_intersection(
    segment_type const &line_a, segment_type const &line_b) {
    auto const &[x1, y1, x2, y2] = line_a;
    auto const &[x3, y3, x4, y4] = line_b;

    bool const is_a_horizontal = y1 == y2;
    bool const is_b_horizontal = y3 == y4;

    if (is_a_horizontal != is_b_horizontal) {
        auto const &[hx1, hy1, hx2, hy2] = (is_a_horizontal) ? line_a : line_b;
        auto const &[vx1, vy1, vx2, vy2] = (is_a_horizontal) ? line_b : line_a;

        if ((min(hx1, hx2) <= vx1 && vx1 <= max(hx1, hx2)) &&
            (min(vy1, vy2) <= hy1 && hy1 <= max(vy1, vy2))) {
            return make_pair(true, make_pair(vx1, hy1));
        }
    }
    return make_pair(false, make_pair(0, 0));
}

std::string solve_part1(const string &input_string) {
    auto const &[line1, line2] = transform_input(input_string);

    vector<int32_t> output{};

    for (auto const &seg1 : line1) {
        for (auto const &seg2 : line2) {
            auto const [valid, pos] = check_intersection(seg1, seg2);

            if (valid && pos != pair<int32_t, int32_t>{0, 0}) {
                output.push_back(abs(pos.first) + abs(pos.second));
            }
        }
    }
    return to_string(*min_element(output.begin(), output.end()));
}

std::string solve_part2(const string &input_string) {
    auto const &[line1, line2] = transform_input(input_string);

    vector<int32_t> output{};

    int32_t dist_seg1{};
    for (auto const &seg1 : line1) {
        int32_t dist_seg2{};
        for (auto const &seg2 : line2) {
            auto const [valid, pos] = check_intersection(seg1, seg2);

            if (valid && pos != pair<int32_t, int32_t>{0, 0}) {
                output.push_back(dist_seg1 + abs(pos.first - seg1.at(0U)) +
                                 abs(pos.second - seg1.at(1U)) + dist_seg2 +
                                 abs(pos.first - seg2.at(0U)) +
                                 abs(pos.second - seg2.at(1U)));
            }
            dist_seg2 +=
                abs(seg2.at(0U) - seg2.at(2U)) + abs(seg2.at(1U) - seg2.at(3U));
        }
        dist_seg1 +=
            abs(seg1.at(0U) - seg1.at(2U)) + abs(seg1.at(1U) - seg1.at(3U));
    }
    return to_string(*min_element(output.begin(), output.end()));
}

}  // namespace day3

}  // namespace year2019
