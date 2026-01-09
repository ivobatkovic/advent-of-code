#include "year2022/day4/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2022 {

namespace day4 {

using namespace std;
using range_type = pair<int32_t, int32_t>;
using input_type = vector<pair<range_type, range_type>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const numbers =
            utils::regex_find_all<int32_t>(line, boost::regex("\\d+"));
        assert(numbers.size() == 4U);
        output.push_back(make_pair(make_pair(numbers.at(0U), numbers.at(1U)),
                                   make_pair(numbers.at(2U), numbers.at(3U))));
    }
    return output;
}

bool contains(range_type const &a, range_type const &b) {
    return (a.first <= b.first && b.second <= a.second);
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(
        input.begin(), input.end(), 0U, [](size_t const acc, auto const &x) {
            return acc +
                   (contains(x.first, x.second) || contains(x.second, x.first));
        }));
}

bool overlaps(range_type const &a, range_type const &b) {
    return (a.first <= b.first) && (b.first <= a.second);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(
        input.begin(), input.end(), 0U, [](size_t const acc, auto const &x) {
            return acc +
                   (overlaps(x.first, x.second) || overlaps(x.second, x.first));
        }));
}

}  // namespace day4

}  // namespace year2022
