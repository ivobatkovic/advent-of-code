#include "year2022/day1/cpp/solutions.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day1 {

using input_type = std::vector<std::vector<size_t>>;

static input_type transform_input(const std::string &input_string) {
    std::vector<std::vector<size_t>> calories_per_elf;
    std::vector<size_t> calories;
    for (auto x : utils::split_string<std::string>(input_string, "\n")) {
        if (x.size() > 0) {
            calories.push_back(std::stoul(x));
        } else {
            calories_per_elf.push_back(calories);
            calories.clear();
        }
    }
    calories_per_elf.push_back(calories);
    return calories_per_elf;
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    std::vector<size_t> total_calories{};
    for (auto &calories : input) {
        total_calories.push_back(
            std::accumulate(calories.begin(), calories.end(), 0U));
    }
    return std::to_string(
        *std::max_element(total_calories.begin(), total_calories.end()));
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    std::vector<size_t> total_calories{};
    for (auto &calories : input) {
        total_calories.push_back(
            std::accumulate(calories.begin(), calories.end(), 0U));
    }
    std::sort(total_calories.begin(), total_calories.end(), std::greater<>());
    return std::to_string(std::accumulate(total_calories.begin(),
                                          total_calories.begin() + 3U, 0U));
}

}  // namespace day1

}  // namespace year2022
