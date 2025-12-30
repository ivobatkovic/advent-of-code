#include "year2025/day2/cpp/solutions.hpp"

#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2025 {

namespace day2 {

using namespace std;
using input_type = vector<pair<int64_t, int64_t>>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &id_ranges :
         utils::split_string<string>(input_string, ",")) {
        auto const ids = utils::split_string<int64_t>(id_ranges, "-");
        output.push_back(make_pair(ids.front(), ids.back()));
    }
    return output;
}

bool is_invalid(int64_t x, bool check_repeating = false) {
    vector<int8_t> digits{};
    while (x > 0) {
        digits.push_back(static_cast<int8_t>(x % 10));
        x /= 10;
    }

    if (!check_repeating && digits.size() % 2U == 1U) {
        return false;
    }

    size_t N = digits.size();
    size_t stop = (check_repeating) ? 0U : N / 2U - 1U;

    for (size_t i{N / 2}; i > stop; --i) {
        vector<int8_t> x_{};
        for (size_t k{0U}; k < N / i; ++k) {
            copy(digits.begin(), digits.begin() + static_cast<int64_t>(i),
                 back_inserter(x_));
        }
        if (digits == x_) {
            return true;
        }
    }
    return false;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t output{0};

    for (auto const &[id0, id1] : input) {
        for (int64_t num{id0}; num < id1 + 1; ++num) {
            if (is_invalid(num)) {
                output += num;
            }
        }
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t output{0};

    for (auto const &[id0, id1] : input) {
        for (int64_t num{id0}; num < id1 + 1; ++num) {
            if (is_invalid(num, true)) {
                output += num;
            }
        }
    }
    return to_string(output);
}

}  // namespace day2

}  // namespace year2025
