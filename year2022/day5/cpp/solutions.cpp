#include "year2022/day5/cpp/solutions.hpp"

#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day5 {

using namespace std;
using input_type =
    tuple<unordered_map<size_t, vector<char>>, vector<array<size_t, 3U>>>;

static input_type transform_input(const string &input_string) {
    // Split the cargo with the instructions
    auto rows = utils::split_string<string>(input_string, "\n\n");

    unordered_map<size_t, vector<char>> stacks{};
    auto cargo = utils::split_string<string>(rows[0], "\n");
    for (auto it = utils::offset_iterator(cargo.rbegin(), 1);
         it != cargo.rend(); ++it) {
        for (size_t k = 0; 4 * k + 1 < (*it).size(); k++) {
            if ((*it)[4 * k + 1] != ' ') {
                stacks[k + 1].push_back((*it)[4 * k + 1]);
            }
        }
    }

    vector<array<size_t, 3U>> instructions{};
    regex r("\\d+");
    for (auto &row : utils::split_string<string>(rows[1], "\n")) {
        auto matches = utils::regex_find_all<size_t>(row, r);
        instructions.push_back({matches[0U], matches[1U], matches[2U]});
    }

    return make_tuple(stacks, instructions);
}

void move_stacks(unordered_map<size_t, vector<char>> &stacks,
                 const size_t n_items, const size_t dst, const size_t src,
                 bool reverse = true) {
    vector<char> items;
    copy(utils::offset_iterator(stacks[dst].cend(), int(-n_items)),
         stacks[dst].cend(), back_inserter(items));
    if (reverse) {
        std::reverse(items.begin(), items.end());
    }

    stacks[dst].erase(utils::offset_iterator(stacks[dst].end(), int(-n_items)),
                      stacks[dst].end());
    stacks[src].insert(stacks[src].end(), items.begin(), items.end());
}

string solve_part1(const string &input_string) {
    auto [stacks, instructions] = transform_input(input_string);
    for (auto &[n_items, dst, src] : instructions) {
        move_stacks(stacks, n_items, dst, src);
    }

    string output{};
    for (size_t i = 1; i < stacks.size() + 1; ++i) {
        output += stacks[i].back();
    }
    return output;
}

string solve_part2(const string &input_string) {
    auto [stacks, instructions] = transform_input(input_string);
    for (auto &[n_items, dst, src] : instructions) {
        move_stacks(stacks, n_items, dst, src, false);
    }

    string output{};
    for (size_t i = 1; i < stacks.size() + 1; ++i) {
        output += stacks[i].back();
    }
    return output;
}

}  // namespace day5

}  // namespace year2022
