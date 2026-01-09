#include "year2019/day4/cpp/solutions.hpp"

#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2019 {

namespace day4 {

using namespace std;

using digits_type = vector<int8_t>;
using input_type = vector<pair<digits_type, digits_type>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const numbers =
            utils::regex_find_all<string>(line, boost::regex("\\d+"));
        assert(numbers.size() == 2U);

        digits_type start{};
        for (char const &chr : numbers.front()) {
            start.push_back(static_cast<int8_t>(chr - '0'));
        }

        digits_type stop{};
        for (char const &chr : numbers.back()) {
            stop.push_back(static_cast<int8_t>(chr - '0'));
        }

        output.push_back({start, stop});
    }
    return output;
}

void make_monotonic(digits_type &digits) {
    for (size_t i{0U}; i < digits.size() - 1U; ++i) {
        if (digits[i] > digits[i + 1U]) {
            for (size_t j{i + 1U}; j < digits.size(); ++j) {
                digits[j] = digits[i];
            }
            return;
        }
    }
}

void next_monotonic(digits_type &digits) {
    for (int8_t i{static_cast<int8_t>(digits.size() - 1U)}; i > -1; --i) {
        if (digits[static_cast<size_t>(i)] < 9) {
            digits[static_cast<size_t>(i)]++;
            for (size_t j{static_cast<size_t>(i)}; j < digits.size(); ++j) {
                digits[j] = digits[static_cast<size_t>(i)];
            }
            return;
        }
    }
}

bool is_double_digit(digits_type const &digits, bool part_two = false) {
    for (size_t i{0U}; i < digits.size() - 1U; ++i) {
        if (digits[i] == digits[i + 1]) {
            if (!part_two) {
                return true;
            }
            if (i == 0 && digits[i + 1U] != digits[i + 2U]) {
                return true;
            }

            else if (i == digits.size() - 2U && digits[i - 1U] != digits[i]) {
                return true;
            }

            else if (digits[i - 1U] != digits[i] &&
                     digits[i] != digits[i + 2U]) {
                return true;
            }
        }
    }

    return false;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    for (auto &[start, stop] : input) {
        make_monotonic(start);
        while (start <= stop) {
            output += is_double_digit(start);
            next_monotonic(start);
        }
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    for (auto &[start, stop] : input) {
        make_monotonic(start);
        while (start <= stop) {
            output += is_double_digit(start, true);
            next_monotonic(start);
        }
    }
    return to_string(output);
}

}  // namespace day4

}  // namespace year2019
