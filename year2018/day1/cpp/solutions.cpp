#include "year2018/day1/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2018 {

namespace day1 {

using namespace std;
using input_type = vector<int32_t>;

static input_type transform_input(const string &input_string) {
    input_type output = utils::split_string<int32_t>(input_string, "\n");
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t output = reduce(input.begin(), input.end(), 0);
    return std::to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    unordered_set<int32_t> visited{};
    int32_t frequency{0};

    while (true) {
        for (auto const &x : input) {
            if (visited.contains(frequency)) {
                return std::to_string(frequency);
            }
            visited.insert(frequency);
            frequency += x;
        }
    }
    return "0";
}

}  // namespace day1

}  // namespace year2018
