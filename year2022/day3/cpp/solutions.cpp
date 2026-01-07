#include "year2022/day3/cpp/solutions.hpp"

#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2022 {

namespace day3 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

int32_t get_priority(char const chr) {
    return (chr > 'a') ? chr + (-'a' + 1) : chr - 'A' + 27;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t output{};

    for (auto const &line : input) {
        unordered_set<char> left(line.begin(), line.begin() + line.size() / 2);
        unordered_set<char> right(line.begin() + line.size() / 2, line.end());

        for (auto const &x : left) {
            if (right.contains(x)) {
                output += get_priority(x);
            }
        }
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t output{};
    for (size_t i{0U}; i < input.size() / 3; ++i) {
        unordered_set<char> one(input.at(3U * i).begin(),
                                input.at(3U * i).end());
        unordered_set<char> two(input.at(3U * i + 1U).begin(),
                                input.at(3U * i + 1U).end());
        unordered_set<char> three(input.at(3U * i + 2U).begin(),
                                  input.at(3U * i + 2U).end());

        for (auto const &x : one) {
            if (two.contains(x) and three.contains(x)) {
                output += get_priority(x);
            }
        }
    }
    return to_string(output);
}

}  // namespace day3

}  // namespace year2022
