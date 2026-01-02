#include "year2017/day2/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2017 {

namespace day2 {

using namespace std;

using row_type = vector<int32_t>;
using input_type = vector<row_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        output.push_back(
            utils::regex_find_all<int32_t>(line, boost::regex("\\d+")));
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    auto const diff = [](int acc, row_type x) {
        return acc + abs(*max_element(x.begin(), x.end()) -
                         *min_element(x.begin(), x.end()));
    };

    return to_string(accumulate(input.begin(), input.end(), 0, diff));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int32_t output{};
    for (auto const &row : input) {
        row_type sorted_row{row};
        std::sort(sorted_row.begin(), sorted_row.end(),
                  std::greater<int32_t>());

        for (size_t i{0U}; i < sorted_row.size() - 1U; ++i) {
            for (size_t j{i + 1U}; j < sorted_row.size(); ++j) {
                if (sorted_row.at(i) % sorted_row.at(j) == 0) {
                    output += sorted_row.at(i) / sorted_row.at(j);
                }
            }
        }
    }
    return to_string(output);
}

}  // namespace day2

}  // namespace year2017
