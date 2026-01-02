#include "year2022/day2/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

namespace year2022 {

namespace day2 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

unordered_map<string, int32_t> score_part_one{
    {"A X", 3 + 1}, {"A Y", 6 + 2}, {"A Z", 0 + 3},
    {"B X", 0 + 1}, {"B Y", 3 + 2}, {"B Z", 6 + 3},
    {"C X", 6 + 1}, {"C Y", 0 + 2}, {"C Z", 3 + 3},
};

unordered_map<string, int32_t> score_part_two{
    {"A X", 0 + 3}, {"A Y", 3 + 1}, {"A Z", 6 + 2},
    {"B X", 0 + 1}, {"B Y", 3 + 2}, {"B Z", 6 + 3},
    {"C X", 0 + 2}, {"C Y", 3 + 3}, {"C Z", 6 + 1},
};

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(
        input.begin(), input.end(), 0,
        [](int32_t acc, string x) { return acc + score_part_one[x]; }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(
        input.begin(), input.end(), 0,
        [](int32_t acc, string x) { return acc + score_part_two[x]; }));
    return "Implement part two";
}

}  // namespace day2

}  // namespace year2022
