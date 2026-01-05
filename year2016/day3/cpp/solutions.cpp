#include "year2016/day3/cpp/solutions.hpp"

#include <array>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2016 {

namespace day3 {

using namespace std;
using input_type = vector<array<int32_t, 3U>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const digits =
            utils::regex_find_all<int32_t>(line, boost::regex("\\d+"));
        assert(digits.size() == 3U);
        output.push_back(
            array<int32_t, 3U>{digits.at(0U), digits.at(1U), digits.at(2)});
    }

    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};
    for (auto &x : input) {
        std::sort(x.begin(), x.end());
        auto const &[a, b, c] = x;

        if (a + b > c) {
            output++;
        }
    }

    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};
    for (size_t i{}; i < input.size() / 3; ++i) {
        for (size_t j{}; j < 3; j++) {
            array<int32_t, 3U> x{input.at(3 * i).at(j),
                                 input.at(3 * i + 1).at(j),
                                 input.at(3 * i + 2).at(j)};
            sort(x.begin(), x.end());
            auto const &[a, b, c] = x;
            if (a + b > c) {
                output++;
            }
        }
    }
    return to_string(output);
}

}  // namespace day3

}  // namespace year2016
