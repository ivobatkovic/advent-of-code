#include "year2022/day6/cpp/solutions.hpp"

#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2022 {

namespace day6 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

size_t find_marker(string const &msg, size_t length = 4U) {
    for (size_t i{0U}; i < msg.size() - length; ++i) {
        int64_t a = static_cast<int64_t>(i);
        int64_t b = static_cast<int64_t>(i + length);
        unordered_set<char> set(msg.begin() + a, msg.begin() + b);

        if (set.size() == length) {
            return i + length;
        }
    }

    return 0U;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};
    for (auto const &msg : input) {
        output += find_marker(msg);
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};
    for (auto const &msg : input) {
        output += find_marker(msg, 14U);
    }
    return to_string(output);
}

}  // namespace day6

}  // namespace year2022
