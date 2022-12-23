#include "year2022/day13/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day13 {

using input_type = std::vector<std::string>;

static input_type transform_input(const std::string &input_string) {
    static_cast<void>(input_string);
    return input_type{};
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    return "Implement part one";
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    return "Implement part two";
}

}  // namespace day13

}  // namespace year2022
