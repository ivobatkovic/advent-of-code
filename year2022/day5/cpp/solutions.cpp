#include "year2022/day5/cpp/solutions.hpp"

#include <iterator>
#include <ranges>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2022 {

namespace day5 {

using namespace std;
using stacks_type = vector<vector<char>>;
using instructions_type = vector<array<int32_t, 3U>>;
using input_type = pair<stacks_type, instructions_type>;

static input_type transform_input(const string &input_string) {
    vector<string> split = utils::split_string<string>(input_string, "\n\n");
    assert(split.size() == 2U);

    auto const crates = utils::split_string<string>(split.front(), "\n");
    size_t num_stacks =
        utils::regex_find_all<int32_t>(crates.back(), boost::regex("\\d+"))
            .size();

    stacks_type stacks{num_stacks};
    for (auto const &line : views::reverse(crates)) {
        for (size_t i{0U}; i < num_stacks; ++i) {
            if ('A' <= line.at(1U + 4 * i) && line.at(1U + 4 * i) <= 'Z') {
                stacks.at(i).push_back(line.at(1U + 4 * i));
            }
        }
    }

    instructions_type instructions{};
    for (auto const &instruction :
         utils::split_string<string>(split.back(), "\n")) {
        auto const digits =
            utils::regex_find_all<int32_t>(instruction, boost::regex("\\d+"));
        assert(digits.size() == 3U);
        instructions.push_back({digits.at(0U), digits.at(1U), digits.at(2U)});
    }
    return make_pair(stacks, instructions);
}

std::string solve(stacks_type &stacks, instructions_type const &instructions,
                  bool const part_two = false) {
    for (auto const &[num, src, dst] : instructions) {
        auto &src_stack = stacks.at(static_cast<size_t>(src) - 1U);
        auto &dst_stack = stacks.at(static_cast<size_t>(dst) - 1U);

        if (part_two) {
            dst_stack.insert(dst_stack.end(),
                             std::make_move_iterator(src_stack.end() - num),
                             std::make_move_iterator(src_stack.end()));
        } else {
            dst_stack.insert(dst_stack.end(),
                             std::make_move_iterator(src_stack.rbegin()),
                             std::make_move_iterator(src_stack.rbegin() + num));
        }
        src_stack.erase(src_stack.end() - num, src_stack.end());
    }

    std::string output{};
    for (auto const &stack : stacks) {
        output += stack.back();
    }

    return output;
}

std::string solve_part1(const string &input_string) {
    auto [stacks, instructions] = transform_input(input_string);
    return solve(stacks, instructions);
}

std::string solve_part2(const string &input_string) {
    auto [stacks, instructions] = transform_input(input_string);
    return solve(stacks, instructions, true);
}

}  // namespace day5

}  // namespace year2022
