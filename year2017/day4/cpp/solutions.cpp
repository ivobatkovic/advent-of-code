#include "year2017/day4/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2017 {

namespace day4 {

using namespace std;
using input_type = vector<vector<string>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        output.push_back(utils::split_string<string>(line, " "));
    }
    return output;
}

bool is_valid(vector<string> const &words, bool const part_two = false) {
    unordered_set<string> seen{};

    for (string word : words) {
        if (part_two) {
            sort(word.begin(), word.end());
        }

        if (seen.contains(word)) {
            return false;
        }
        seen.insert(word);
    }
    return true;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(input.begin(), input.end(), 0U,
                                [](size_t const acc, auto const &words) {
                                    return acc + is_valid(words);
                                }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(accumulate(input.begin(), input.end(), 0U,
                                [](size_t const acc, auto const &words) {
                                    return acc + is_valid(words, true);
                                }));
}

}  // namespace day4

}  // namespace year2017
