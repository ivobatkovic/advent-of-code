#include "year2016/day1/cpp/solutions.hpp"

#include <cmath>
#include <functional>
#include <numbers>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/cpp_utils.hpp"

template <>
struct std::hash<std::pair<int64_t, int64_t>> {
    size_t operator()(const pair<int64_t, int64_t> &p) const {
        return hash<int64_t>{}(p.first) * 31 + hash<int64_t>{}(p.second);
    }
};

namespace year2016 {

namespace day1 {

using namespace std;
using input_type = vector<std::pair<char, int64_t>>;

static input_type transform_input(const string &input_string) {
    vector<string> split = utils::split_string<string>(input_string, ", ");

    input_type output{};
    for (string const &x : split) {
        string digits = x.substr(1, x.size());
        output.push_back({x[0], std::stoi(digits)});
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t x{}, y{};
    double direction{numbers::pi / 2.0};

    for (auto &[d, step] : input) {
        direction += (d == 'L') ? numbers::pi / 2.0 : -numbers::pi / 2.0;
        x += step * static_cast<int64_t>(std::round(cos(direction)));
        y += step * static_cast<int64_t>(std::round(sin(direction)));
    }

    return std::to_string(std::abs(x) + std::abs(y));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t x{}, y{};
    double direction{numbers::pi / 2.0};

    unordered_set<pair<int64_t, int64_t>> visited{};

    for (auto &[d, step] : input) {
        direction += (d == 'L') ? numbers::pi / 2.0 : -numbers::pi / 2.0;

        for (int64_t s{0U}; s < step; ++s) {
            if (visited.contains({x, y})) {
                return to_string(abs(x) + abs(y));
            }
            visited.insert({x, y});
            x += static_cast<int64_t>(std::round(cos(direction)));
            y += static_cast<int64_t>(std::round(sin(direction)));
        }
    }

    return "0";
}

}  // namespace day1

}  // namespace year2016
