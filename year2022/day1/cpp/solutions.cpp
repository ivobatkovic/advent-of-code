#include "year2022/day1/cpp/solutions.hpp"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2022 {

namespace day1 {

using namespace std;
using input_type = vector<int64_t>;

static input_type transform_input(const string &input_string) {
    input_type outputs{};
    int64_t tot_calories{0U};

    for (auto line : utils::split_string<string>(input_string, "\n")) {
        if (line == "") {
            outputs.push_back(tot_calories);
            tot_calories = 0U;
        } else {
            tot_calories += stoi(line);
        }
    }

    if (tot_calories > 0U) {
        outputs.push_back(tot_calories);
    }
    return outputs;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(*std::max_element(input.begin(), input.end()));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    sort(input.begin(), input.end(), std::greater<int64_t>());
    return to_string(accumulate(input.begin(), input.begin() + 3, 0));
}

}  // namespace day1

}  // namespace year2022
