#include "year2020/day3/cpp/solutions.hpp"

#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2020 {

namespace day3 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t const height = input.size();
    size_t const width = input.front().size();

    size_t px{}, py{};
    size_t dx{3}, dy{1};
    size_t output{};

    while (py < height) {
        if (input.at(py).at(px) == '#') {
            output += 1;
        }

        px = (px + dx) % width;
        py += dy;
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t const height = input.size();
    size_t const width = input.front().size();

    size_t output{1U};

    array<pair<int32_t, int32_t>, 5U> slopes{
        make_pair(1, 1), make_pair(3, 1), make_pair(5, 1),
        make_pair(7, 1), make_pair(1, 2),
    };

    for (auto const &[dx, dy] : slopes) {
        size_t px{}, py{};
        size_t num_trees{};

        while (py < height) {
            if (input.at(py).at(px) == '#') {
                num_trees += 1;
            }

            px = (px + static_cast<size_t>(dx)) % width;
            py += static_cast<size_t>(dy);
        }

        output *= (num_trees > 0) ? num_trees : 1U;
    }
    return to_string(output);
}

}  // namespace day3

}  // namespace year2020
