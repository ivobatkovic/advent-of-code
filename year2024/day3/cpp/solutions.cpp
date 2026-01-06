#include "year2024/day3/cpp/solutions.hpp"

#include <boost/regex/v5/regex_iterator.hpp>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2024 {

namespace day3 {

using namespace std;
using input_type = vector<pair<int32_t, int32_t>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    boost::regex exp("mul\\((\\d+),(\\d+)\\)");
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        boost::sregex_iterator end{};

        boost::sregex_iterator it{line.begin(), line.end(), exp};
        for (; it != end; ++it) {
            output.push_back({stoi(it->str(1)), stoi(it->str(2))});
        }
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(input.begin(), input.end(), 0,
                                [](int32_t const acc, auto const &pair) {
                                    return acc + pair.first * pair.second;
                                }));
}

static input_type transform_input_part_two(const string &input_string,
                                           bool enable = true) {
    input_type output{};

    boost::regex exp("do\\(\\)|don't\\(\\)|mul\\((\\d+),(\\d+)\\)");
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        boost::sregex_iterator end{};

        boost::sregex_iterator it{line.begin(), line.end(), exp};
        for (; it != end; ++it) {
            string const match = it->str();

            if (match == "don't()") {
                enable = false;
            } else if (match == "do()") {
                enable = true;
            } else if (enable) {
                output.push_back({stoi(it->str(1)), stoi(it->str(2))});
            }
        }
    }
    return output;
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input_part_two(input_string);

    return to_string(accumulate(input.begin(), input.end(), 0,
                                [](int32_t const acc, auto const &pair) {
                                    return acc + pair.first * pair.second;
                                }));
}

}  // namespace day3

}  // namespace year2024
