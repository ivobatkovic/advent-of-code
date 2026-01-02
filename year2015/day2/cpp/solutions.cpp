#include "year2015/day2/cpp/solutions.hpp"

#include <array>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2015 {

namespace day2 {

using namespace std;
using dim_type = array<int64_t, 3U>;
using input_type = vector<dim_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const dimensions =
            utils::regex_find_all<int64_t>(line, boost::regex("\\d+"));
        assert(dimensions.size() == 3U);
        output.push_back(
            {dimensions.at(0U), dimensions.at(1U), dimensions.at(2U)});
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t output{};

    for (auto &dimensions : input) {
        sort(dimensions.begin(), dimensions.end());
        auto const &[a, b, c] = dimensions;
        output += 2 * (a * b + a * c + b * c) + a * b;
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    int64_t output{};

    for (auto &dimensions : input) {
        sort(dimensions.begin(), dimensions.end());
        auto const &[a, b, c] = dimensions;
        output += 2 * (a + b) + a * b * c;
    }
    return to_string(output);
}

}  // namespace day2

}  // namespace year2015
