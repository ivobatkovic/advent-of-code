#include "year2020/day6/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2020 {

namespace day6 {

using namespace std;
using set_type = unordered_set<char>;
using group_type = vector<set_type>;
using input_type = vector<group_type>;

static input_type transform_input(const string &input_string) {
    auto const groups = utils::split_string<string>(input_string, "\n\n");

    input_type output{};

    for (auto const &group : groups) {
        group_type group_answers{};
        for (auto const &answer : utils::split_string<string>(group, "\n")) {
            group_answers.push_back(set_type{answer.begin(), answer.end()});
        }
        output.push_back(group_answers);
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    size_t output{};

    for (auto const &group : transform_input(input_string)) {
        set_type union_{};
        for (set_type const &set : group) {
            union_.insert(set.begin(), set.end());
        }
        output += union_.size();
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    size_t output{};

    for (group_type const &group : transform_input(input_string)) {
        set_type keys{group.front().begin(), group.front().end()};

        for (auto const &key : keys) {
            bool overlaps{true};
            for (set_type const &set : group) {
                if (!set.contains(key)) {
                    overlaps = false;
                    break;
                }
            }
            output += overlaps;
        }
    }
    return to_string(output);
}

}  // namespace day6

}  // namespace year2020
