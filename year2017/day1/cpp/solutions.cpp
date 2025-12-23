#include "year2017/day1/cpp/solutions.hpp"

#include <string>
#include <vector>

namespace year2017 {

namespace day1 {

using namespace std;
using input_type = vector<int32_t>;

static input_type transform_input(const string &input_string) {
    input_type out{};
    for (char const &x : input_string) {
        out.push_back(x - '0');
    }
    return out;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    input_type input_aug{input};
    input_aug.insert(input_aug.end(), input.begin(), input.begin() + 1);

    int output = 0;
    for (size_t i{0U}; i < input.size(); ++i)
        if (input[i] == input_aug[i + 1]) {
            output += input[i];
        }

    return std::to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    size_t N = input.size() / 2;

    input_type input_aug{input};
    input_aug.insert(input_aug.end(), input.begin(), input.begin() + N);

    int output = 0;
    for (size_t i{0U}; i < input.size(); ++i)
        if (input[i] == input_aug[i + N]) {
            output += input[i];
        }
    return std::to_string(output);
}

}  // namespace day1

}  // namespace year2017
