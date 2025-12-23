#include "year2019/day1/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2019 {

namespace day1 {

using namespace std;
using input_type = vector<uint64_t>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<uint64_t>(input_string, "\n");
}

uint64_t needed_fuel(uint64_t const mass) {
    if (mass == 0) {
        return 0L;
    }

    uint64_t fuel = (mass / 3 > 2) ? mass / 3 - 2 : 0;

    return fuel + needed_fuel(fuel);
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(
        reduce(input.begin(), input.end(), 0,
               [](int64_t acc, int64_t x) { return acc + x / 3 - 2; }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    uint64_t output{0};
    for (auto &x : input) {
        output += needed_fuel(x);
    }
    return to_string(output);
}

}  // namespace day1

}  // namespace year2019
