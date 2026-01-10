#include "year2017/day5/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2017 {

namespace day5 {

using namespace std;
using input_type = vector<int32_t>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<int32_t>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t max_val = static_cast<int32_t>(input.size()) - 1;
    int32_t offset = 0;
    size_t count{};

    while (true) {
        if (offset < 0 || offset > max_val) {
            return to_string(count);
        }

        int32_t &x = input[static_cast<size_t>(offset)];
        int32_t const jump = x;
        x++;
        offset += jump;
        ++count;
    }

    return "0";
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t max_val = static_cast<int32_t>(input.size()) - 1;
    int32_t offset = 0;
    size_t count{};

    while (true) {
        if (offset < 0 || offset > max_val) {
            return to_string(count);
        }

        int32_t &x = input[static_cast<size_t>(offset)];
        int32_t const jump = x;

        x = (jump >= 3) ? x - 1 : x + 1;
        offset += jump;
        ++count;
    }

    return "0";
}

}  // namespace day5

}  // namespace year2017
