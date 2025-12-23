#include "year2015/day1/cpp/solutions.hpp"

#include <cstdint>
#include <numeric>
#include <string>
#include <vector>

namespace year2015 {

namespace day1 {

using namespace std;
using input_type = vector<int64_t>;

static input_type transform_input(const string &input_string) {
    input_type data{};
    for (auto &x : input_string) {
        data.push_back((x == '(') ? 1 : -1);
    }

    static_cast<void>(input_string);
    return data;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return std::to_string(std::reduce(input.begin(), input.end(), 0));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t floor{0U};
    for (std::size_t i{0U}; i < input.size(); ++i) {
        if (floor == -1) {
            return std::to_string(i);
        }
        floor += input.at(i);
    }
    return "Failed to find the solution";
}

}  // namespace day1

}  // namespace year2015
