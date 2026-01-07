#include "year2015/day3/cpp/solutions.hpp"

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2015 {

namespace day3 {

using namespace std;
using step_type = pair<int32_t, int32_t>;
using input_type = vector<step_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto &chr : input_string) {
        if (chr == '<') {
            output.push_back({-1, 0});
        } else if (chr == '>') {
            output.push_back({1, 0});
        } else if (chr == '^') {
            output.push_back({0, 1});
        } else if (chr == 'v') {
            output.push_back({0, -1});
        }
    }
    return output;
}

size_t visited_houses(input_type const &steps,
                      unordered_set<step_type> &visited, step_type pos = {}) {
    visited.insert(pos);

    for (auto const &[dx, dy] : steps) {
        pos = step_type{pos.first + dx, pos.second + dy};
        visited.insert(pos);
    }
    return visited.size();
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    unordered_set<step_type> visited{};
    return to_string(visited_houses(input, visited));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    unordered_set<step_type> visited{};

    input_type santa{};
    for (auto it = input.begin(); it < input.end(); it += 2) {
        santa.push_back(*it);
    }
    visited_houses(santa, visited);

    input_type robot{};
    for (auto it = input.begin() + 1; it < input.end(); it += 2) {
        robot.push_back(*it);
    }

    return to_string(visited_houses(robot, visited));
}

}  // namespace day3

}  // namespace year2015
