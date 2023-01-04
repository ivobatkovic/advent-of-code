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

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

int priority(set<char> const &characters) {
    int total{0U};
    for (auto character : characters) {
        total +=
            (islower(character)) ? character + 1 - 'a' : character + 27 - 'A';
    }
    return total;
}

set<char> intersect(vector<string> const &rucksacks) {
    if (rucksacks.size() == 0) {
        return set<char>{};
    }

    set<char> output(rucksacks.at(0).begin(), rucksacks.at(0).end());
    for (size_t i{1U}; i < rucksacks.size(); ++i) {
        set<char> intersection;
        set<char> rucksack(rucksacks.at(i).begin(), rucksacks.at(i).end());

        set_intersection(output.begin(), output.end(), rucksack.begin(),
                         rucksack.end(),
                         inserter(intersection, intersection.begin()));

        output = intersection;
    }
    return output;
}

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    int total{0};
    for (auto &rucksack : input) {
        total += priority(intersect(
            {rucksack.substr(0, rucksack.size() / 2),
             rucksack.substr(rucksack.size() / 2, rucksack.size() / 2)}));
    }
    return to_string(total);
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    int total{0};
    for (size_t i{0U}; i < input.size(); i += 3) {
        total += priority(intersect({input[i], input[i + 1], input[i + 2]}));
    }
    return to_string(total);
}

}  // namespace day3

}  // namespace year2022
