#include "solutions.hpp"

#include <iostream>

#include "cpp_utils.hpp"

namespace day1 {

using input_type = std::vector<std::string>;

static input_type transform_input(const std::string &input_string) {
    return utils::split_string<std::string>(input_string, '\n');
}

std::string read_input(std::string file_name) {
    return utils::read_file_to_string(file_name);
}

// Implement part one solution
output_type solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    int fuel_needed = 0;
    for (auto &mass : input) {
        fuel_needed += int(std::stoi(mass) / 3.0) - 2;
    }
    return std::to_string(fuel_needed);
}

static int compute_fuel(int mass) {
    const int fuel_needed = int(mass / 3.0) - 2;
    return (fuel_needed < 0) ? 0 : fuel_needed + compute_fuel(fuel_needed);
}

// Implement part two solution
output_type solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    int fuel_needed = 0;
    for (auto &mass : input) {
        fuel_needed += compute_fuel(std::stoi(mass));
    }
    return std::to_string(fuel_needed);
}

}  // namespace day1
