#include "year2025/day5/cpp/solutions.hpp"

#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2025 {

namespace day5 {

using namespace std;

using ranges_type = vector<pair<int64_t, int64_t>>;
using ingredients_type = vector<int64_t>;
using input_type = pair<ranges_type, ingredients_type>;

static input_type transform_input(const string &input_string) {
    auto const split = utils::split_string<string>(input_string, "\n\n");
    assert(split.size() == 2U);

    boost::regex const regex("\\d+");

    auto const &ranges_str = split.front();
    auto const &ingredients_str = split.back();

    ranges_type ranges{};
    for (auto const &range : utils::split_string<string>(ranges_str, "\n")) {
        auto const numbers = utils::regex_find_all<int64_t>(range, regex);
        assert(numbers.size() == 2U);
        ranges.push_back({numbers.front(), numbers.back()});
    }

    ingredients_type ingredients =
        utils::regex_find_all<int64_t>(ingredients_str, regex);

    return {ranges, ingredients};
}

bool is_ingredient_in_ranges(int64_t const ingredient,
                             ranges_type const &ranges) {
    for (auto const &[lo, hi] : ranges) {
        if (lo <= ingredient && ingredient <= hi) {
            return true;
        }
    }
    return false;
}

std::string solve_part1(const string &input_string) {
    auto const &[ranges, ingredients] = transform_input(input_string);

    size_t output{};
    for (auto const &ingredient : ingredients) {
        output += is_ingredient_in_ranges(ingredient, ranges);
    }
    return to_string(output);
}

ranges_type propagate_ranges(ranges_type &ranges) {
    std::sort(ranges.begin(), ranges.end(),
              [](auto const &a, auto const &b) { return a.first < b.first; });

    ranges_type output{ranges.front()};

    for (auto it = ranges.begin() + 1; it != ranges.end(); ++it) {
        if (output.back().second < it->first) {
            output.push_back(*it);

        } else {
            output.back().second = max(output.back().second, it->second);
        }
    }
    return output;
}

std::string solve_part2(const string &input_string) {
    auto [ranges, ingredients] = transform_input(input_string);

    ranges = propagate_ranges(ranges);

    int64_t output{};
    for (auto const &[lo, hi] : ranges) {
        output += hi - lo + 1;
    }

    return to_string(output);
}

}  // namespace day5

}  // namespace year2025
