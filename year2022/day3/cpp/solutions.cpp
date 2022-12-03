#include "year2022/day3/cpp/solutions.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day3 {

using input_type = std::vector<std::string>;

static input_type transform_input(const std::string &input_string) {
    return utils::split_string<std::string>(input_string, "\n");
}

int priority(std::set<char> const &characters) {
    int total{0U};
    for (auto character : characters) {
        total +=
            (islower(character)) ? character + 1 - 'a' : character + 27 - 'A';
    }
    return total;
}

std::set<char> intersect(std::vector<std::string> const &rucksacks) {
    if (rucksacks.size() == 0) {
        return std::set<char>{};
    }

    std::set<char> output(rucksacks.at(0).begin(), rucksacks.at(0).end());
    for (std::size_t i{1U}; i < rucksacks.size(); ++i) {
        std::set<char> intersection;
        std::set<char> rucksack(rucksacks.at(i).begin(), rucksacks.at(i).end());

        std::set_intersection(
            output.begin(), output.end(), rucksack.begin(), rucksack.end(),
            std::inserter(intersection, intersection.begin()));

        output = intersection;
    }
    return output;
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    int total{0};
    for (auto &rucksack : input) {
        total += priority(intersect(
            {rucksack.substr(0, rucksack.size() / 2),
             rucksack.substr(rucksack.size() / 2, rucksack.size() / 2)}));
    }
    return std::to_string(total);
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    int total{0};
    for (std::size_t i{0U}; i < input.size(); i += 3) {
        total += priority(intersect({input[i], input[i + 1], input[i + 2]}));
    }
    return std::to_string(total);
}

}  // namespace day3

}  // namespace year2022
