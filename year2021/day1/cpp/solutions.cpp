#include "year2021/day1/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2021 {

namespace day1 {

using namespace std;
using input_type = vector<int32_t>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<int32_t>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    vector<int32_t> diff(input.size());
    adjacent_difference(input.begin(), input.end(), diff.begin(),
                        [](int curr, int prev) { return curr > prev; });

    return to_string(accumulate(diff.begin() + 1, diff.end(), 0));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    vector<int32_t> windows{};

    int32_t window{input.at(0U) + input.at(1U) + input.at(2U)};
    windows.push_back(window);
    for (size_t i{3U}; i < input.size(); ++i) {
        window += (input.at(i) - input.at(i - 3U));
        windows.push_back(window);
    }

    vector<int32_t> diff(windows.size());
    adjacent_difference(windows.begin(), windows.end(), diff.begin(),
                        [](int curr, int prev) { return curr > prev; });

    return to_string(accumulate(diff.begin() + 1, diff.end(), 0));
}

}  // namespace day1

}  // namespace year2021
