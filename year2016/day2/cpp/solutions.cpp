#include "year2016/day2/cpp/solutions.hpp"

#include <string>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2016 {

namespace day2 {

using namespace std;

using pos_type = pair<int32_t, int32_t>;
using step_type = vector<pos_type>;
using input_type = vector<step_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        step_type steps{};
        for (auto const &chr : line) {
            if (chr == 'U') {
                steps.push_back({0, -1});

            } else if (chr == 'D') {
                steps.push_back({0, 1});

            } else if (chr == 'L') {
                steps.push_back({-1, 0});

            } else if (chr == 'R') {
                steps.push_back({1, 0});
            }
        }
        output.push_back(steps);
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    std::unordered_map<pos_type, std::string> mapping = {
        {{0, 0}, "1"}, {{1, 0}, "2"}, {{2, 0}, "3"},
        {{0, 1}, "4"}, {{1, 1}, "5"}, {{2, 1}, "6"},
        {{0, 2}, "7"}, {{1, 2}, "8"}, {{2, 2}, "9"},
    };

    pos_type pos = {1, 1};

    string output{};
    for (auto const &entry : input) {
        for (auto const &[dx, dy] : entry) {
            pos_type const new_pos = {pos.first + dx, pos.second + dy};
            if (mapping.contains(new_pos)) {
                pos = new_pos;
            }
        }
        output += mapping[pos];
    }
    return output;
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    std::unordered_map<pos_type, std::string> mapping = {
        {{2, 0}, "1"}, {{1, 1}, "2"}, {{2, 1}, "3"}, {{3, 1}, "4"},
        {{0, 2}, "5"}, {{1, 2}, "6"}, {{2, 2}, "7"}, {{3, 2}, "8"},
        {{4, 2}, "9"}, {{1, 3}, "A"}, {{2, 3}, "B"}, {{3, 3}, "C"},
        {{2, 4}, "D"},
    };

    pos_type pos = {0, 2};

    string output{};
    for (auto const &entry : input) {
        for (auto const &[dx, dy] : entry) {
            pos_type const new_pos = {pos.first + dx, pos.second + dy};
            if (mapping.contains(new_pos)) {
                pos = new_pos;
            }
        }
        output += mapping[pos];
    }
    return output;
}

}  // namespace day2

}  // namespace year2016
