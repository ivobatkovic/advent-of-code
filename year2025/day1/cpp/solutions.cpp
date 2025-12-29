#include "year2025/day1/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2025 {

namespace day1 {

using namespace std;
using input_type = vector<int64_t>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (string const &line : utils::split_string<string>(input_string, "\n")) {
        int64_t const nr{stoi(line.substr(1, line.size()))};
        output.push_back((line.at(0) == 'R') ? nr : -nr);
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t x{50};
    size_t output{0U};

    for (auto &d : input) {
        x = (x + d) % 100;
        if (x == 0) {
            output += 1;
        }
    }

    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    int64_t x{50};
    size_t output{0U};

    for (auto &d : input) {
        output += static_cast<size_t>(abs(d)) / 100U;
        d = d % 100;

        int64_t x_next = ((x + d) % 100 + 100) % 100;

        if (x_next == 0 ||
            (x != 0 && ((x_next > x && d < 0) || (x_next < x && d > 0)))) {
            output += 1;
        }

        x = x_next;
    }

    return to_string(output);
}

}  // namespace day1

}  // namespace year2025
