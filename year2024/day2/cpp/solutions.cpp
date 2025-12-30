#include "year2024/day2/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2024 {

namespace day2 {

using namespace std;
using input_type = vector<vector<int64_t>>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto &line : utils::split_string<string>(input_string, "\n")) {
        output.push_back(utils::split_string<int64_t>(line, " "));
    }
    return output;
}

bool is_safe(vector<int64_t> const &x) {
    if (x.size() == 0) {
        return true;
    }

    vector<int64_t> diff(x.size());
    adjacent_difference(x.begin(), x.end(), diff.begin());

    bool positive = (diff.at(1U) > 0) ? true : false;

    for (auto it = diff.begin() + 1; it != diff.end(); ++it) {
        int64_t const val{*it};

        if (abs(val) < 1 || abs(val) > 3 || (positive && val < 0) ||
            (!positive && val > 0)) {
            return false;
        }
    }

    return true;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(
        input.begin(), input.end(), 0,
        [](int acc, vector<int64_t> const &x) { return acc + is_safe(x); }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    auto const part_two = [](vector<int64_t> const &x) -> int64_t {
        if (is_safe(x)) {
            return 1;
        } else {
            for (size_t i{0U}; i < x.size(); ++i) {
                vector<int64_t> sliced{};
                copy(x.begin(), x.begin() + static_cast<int64_t>(i),
                     back_inserter(sliced));
                copy(x.begin() + static_cast<int64_t>(i) + 1, x.end(),
                     back_inserter(sliced));
                if (is_safe(sliced)) {
                    return 1;
                }
            }
        }
        return 0;
    };

    return to_string(accumulate(input.begin(), input.end(), 0,
                                [part_two](int acc, vector<int64_t> const &x) {
                                    return acc + part_two(x);
                                }));
}

}  // namespace day2

}  // namespace year2024
