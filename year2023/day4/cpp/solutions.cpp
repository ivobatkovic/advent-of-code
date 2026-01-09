#include "year2023/day4/cpp/solutions.hpp"

#include <math.h>

#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2023 {

namespace day4 {

using namespace std;
using numbers_type = vector<int32_t>;
using input_type = vector<pair<numbers_type, numbers_type>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    boost::regex exp("\\d+");
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const left_right = utils::split_string<string>(line, "|");

        auto winning = utils::regex_find_all<int32_t>(left_right.front(), exp);
        winning.erase(winning.begin());
        auto numbers = utils::regex_find_all<int32_t>(left_right.back(), exp);
        output.push_back({winning, numbers});
    }
    return output;
}

set<int32_t> intersect(numbers_type const &winning,
                       numbers_type const &numbers) {
    set<int32_t> winning_set(winning.begin(), winning.end());
    set<int32_t> numbers_set(numbers.begin(), numbers.end());

    set<int32_t> intersection{};
    std::set_intersection(winning_set.begin(), winning_set.end(),
                          numbers_set.begin(), numbers_set.end(),
                          std::inserter(intersection, intersection.begin()));
    return intersection;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};
    for (auto const &[winning, numbers] : input) {
        auto const intersection = intersect(winning, numbers);

        if (intersection.size()) {
            output += static_cast<size_t>(pow(2, intersection.size() - 1U));
        }
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    vector<int32_t> instances(input.size(), 0);
    size_t card{0U};

    for (auto const &[winning, numbers] : input) {
        instances[card]++;

        auto const intersection = intersect(winning, numbers);
        for (size_t i{0U}; i < intersection.size(); ++i) {
            instances[card + (i + 1)] += instances[card];
        }
        card++;
    }

    return to_string(accumulate(instances.begin(), instances.end(), 0));
}

}  // namespace day4

}  // namespace year2023
