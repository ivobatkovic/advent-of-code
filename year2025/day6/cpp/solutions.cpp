#include "year2025/day6/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2025 {

namespace day6 {

using namespace std;

using operators_type = vector<string>;
using numbers_type = vector<vector<string>>;
using input_type = pair<numbers_type, operators_type>;

static input_type transform_input(const string &input_string) {
    vector<string> const lines =
        utils::split_string<string>(input_string, "\n");

    operators_type ops =
        utils::regex_find_all<string>(lines.back(), boost::regex("[*+]\\s*"));

    numbers_type numbers{};

    size_t col{};
    for (auto const &op : ops) {
        vector<string> numbers_in_col{};
        for (size_t row{0U}; row < lines.size() - 1; ++row) {
            numbers_in_col.push_back(lines.at(row).substr(col, op.size()));
        }
        col += op.size();
        numbers.push_back(numbers_in_col);
    }

    return {numbers, ops};
}

vector<int64_t> get_numbers_from_column(size_t const col,
                                        numbers_type const &numbers,
                                        bool const part_two = false) {
    std::vector<int64_t> output;

    if (part_two) {
        auto const &rows = numbers.at(col);
        size_t width = rows.at(0U).size();
        for (size_t i{0U}; i < width; ++i) {
            std::string digits{};
            for (auto const &row : rows) {
                const char chr = row.at(i);
                if (chr != ' ') {
                    digits += chr;
                }
            }
            if (!digits.empty()) {
                output.push_back(std::stoi(digits));
            }
        }
        return output;
    }

    for (auto const &row : numbers.at(col)) {
        output.push_back(stoi(row));
    }
    return output;
}

int64_t compute(char const op, vector<int64_t> const &numbers) {
    if (op == '+') {
        return accumulate(numbers.begin(), numbers.end(), 0LL);
    } else if (op == '*') {
        return accumulate(
            numbers.begin(), numbers.end(), 1LL,
            [](size_t const acc, size_t const x) { return acc * x; });
    }
    return 0;
}

std::string solve_part1(const string &input_string) {
    auto const &[numbers, ops] = transform_input(input_string);

    int64_t output{};
    for (size_t col{0U}; col < ops.size(); ++col) {
        output += compute(ops[col][0], get_numbers_from_column(col, numbers));
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto const &[numbers, ops] = transform_input(input_string);

    int64_t output{};
    for (size_t col{0U}; col < ops.size(); ++col) {
        output +=
            compute(ops[col][0], get_numbers_from_column(col, numbers, true));
    }
    return to_string(output);
}

}  // namespace day6

}  // namespace year2025
