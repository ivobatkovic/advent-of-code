#include "year2023/day1/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

namespace year2023 {

namespace day1 {

using namespace std;
using input_type = vector<int64_t>;

std::unordered_map<string, string> mapping{
    {"one", "1"}, {"1", "1"},    {"two", "2"},   {"2", "2"},    {"three", "3"},
    {"3", "3"},   {"four", "4"}, {"4", "4"},     {"five", "5"}, {"5", "5"},
    {"six", "6"}, {"6", "6"},    {"seven", "7"}, {"7", "7"},    {"eight", "8"},
    {"8", "8"},   {"nine", "9"}, {"9", "9"},
};

static input_type transform_input(const string &input_string,
                                  bool digits = false) {
    input_type output{};

    auto const regex_exp =
        (digits) ? boost::regex(
                       "(?=(one|two|three|four|five|six|seven|eight|nine|\\d))")
                 : boost::regex("(\\d)");

    for (auto &line : utils::split_string<string>(input_string, "\n")) {
        vector<string> match = utils::regex_find_all<string>(line, regex_exp);
        output.push_back(stoi(mapping[match.at(1U)] + mapping[match.back()]));
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(accumulate(input.begin(), input.end(), 0));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string, true);
    return to_string(accumulate(input.begin(), input.end(), 0));
}

}  // namespace day1

}  // namespace year2023
