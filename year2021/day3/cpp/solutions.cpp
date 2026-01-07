#include "year2021/day3/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2021 {

namespace day3 {

using namespace std;
using input_type = vector<vector<bool>>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        vector<bool> bits{};
        for (const char &c : line) {
            bits.push_back((c == '1') ? true : false);
        }
        output.push_back(bits);
    }

    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t gamma{};
    for (size_t i{0U}; i < input.front().size(); ++i) {
        bool const bit = accumulate(input.begin(), input.end(), 0U,
                                    [&i](size_t const acc, auto const &x) {
                                        return (x[i]) ? acc + 1 : acc;
                                    }) > input.size() / 2U;
        gamma = (gamma << 1) | bit;
    }

    int32_t mask = (1 << input.front().size()) - 1;
    int32_t epsilon = gamma ^ mask;

    return to_string(gamma * epsilon);
}

int32_t compute_rating(input_type numbers,
                       std::function<bool(float, float)> op) {
    for (size_t i{0U}; i < numbers.front().size(); ++i) {
        if (numbers.size() == 1) {
            break;
        }

        bool const look_for = op(static_cast<float>(accumulate(
                                     numbers.begin(), numbers.end(), 0U,
                                     [&i](size_t const acc, auto const &x) {
                                         return (x[i]) ? acc + 1 : acc;
                                     })),
                                 static_cast<float>(numbers.size()) / 2.0F);

        input_type new_numbers{};
        for (auto const &number : numbers) {
            if (number.at(i) == look_for) {
                new_numbers.push_back(number);
            }
        }
        numbers = new_numbers;
    }

    int32_t output{};
    for (auto const &bit : numbers.front()) {
        output = (output << 1) | bit;
    }
    return output;
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    auto const geq = [](float const a, float const b) { return a >= b; };
    auto const lt = [](float const a, float const b) { return a < b; };

    return to_string(compute_rating(input, geq) * compute_rating(input, lt));
}

}  // namespace day3

}  // namespace year2021
