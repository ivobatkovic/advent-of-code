#include "year2021/day6/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2021 {

namespace day6 {

using namespace std;
using input_type = vector<size_t>;

static input_type transform_input(const string &input_string) {
    return utils::regex_find_all<size_t>(input_string, boost::regex("\\d"));
}

size_t cycle(input_type const &start_count, size_t days) {
    array<size_t, 9U> fish{};
    for (auto &nr : start_count) {
        fish.at(nr)++;
    }

    for (size_t day{0U}; day < days; ++day) {
        array<size_t, 9U> fish_tmp{};
        for (size_t i{8}; i > 0; --i) {
            fish_tmp.at(i - 1U) = fish.at(i);
        }
        fish_tmp.at(6U) += fish.at(0U);
        fish_tmp.at(8U) = fish.at(0U);
        fish = fish_tmp;
    }

    return accumulate(fish.begin(), fish.end(), 0UL);
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(cycle(input, 80));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(cycle(input, 256));
}

}  // namespace day6

}  // namespace year2021
