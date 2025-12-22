#include "year2020/day1/cpp/solutions.hpp"

#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2020 {

namespace day1 {

using namespace std;
using input_type = vector<int64_t>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<int64_t>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    for (size_t i{0U}; i < input.size() - 1U; ++i) {
        for (size_t j{i}; j < input.size(); ++j) {
            if (input.at(i) + input.at(j) == 2020) {
                return to_string(input.at(i) * input.at(j));
            }
        }
    }
    return "0";
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    for (size_t i{0U}; i < input.size() - 2U; ++i) {
        for (size_t j{i}; j < input.size() - 1; ++j) {
            for (size_t k{j}; k < input.size(); ++k) {
                if (input.at(i) + input.at(j) + input.at(k) == 2020) {
                    return to_string(input.at(i) * input.at(j) * input.at(k));
                }
            }
        }
    }
    return "0";
}

}  // namespace day1

}  // namespace year2020
