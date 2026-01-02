#include "year2021/day2/cpp/solutions.hpp"

#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2021 {

namespace day2 {

using namespace std;
using input_type = vector<pair<int64_t, int64_t>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const direction_and_val = utils::split_string<string>(line, " ");

        if (direction_and_val.front() == "forward") {
            output.push_back({stoi(direction_and_val.back()), 0});
        } else if (direction_and_val.front() == "up") {
            output.push_back({0, -stoi(direction_and_val.back())});
        } else if (direction_and_val.front() == "down") {
            output.push_back({0, stoi(direction_and_val.back())});
        }
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    array<int64_t, 2U> pos{};
    for (auto const &[dx, dy] : input) {
        pos[0] += dx;
        pos[1] += dy;
    }

    return to_string(pos[0] * abs(pos[1]));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    array<int64_t, 2U> pos{};
    int64_t aim{};
    for (auto const &[dx, dy] : input) {
        if (dx) {
            pos[0] += dx;
            pos[1] += aim * dx;
        } else {
            aim += dy;
        }
    }

    return to_string(pos[0] * abs(pos[1]));
}

}  // namespace day2

}  // namespace year2021
