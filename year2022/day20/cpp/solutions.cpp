#include "year2022/day20/cpp/solutions.hpp"

#include <assert.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day20 {

using namespace std;
using tuple_type = tuple<size_t, int64_t>;
using input_type = vector<tuple_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    auto const rows = utils::split_string<int64_t>(input_string, "\n");
    for (size_t i{0U}; i < rows.size(); ++i) {
        output.push_back({i, rows.at(i)});
    }
    return output;
}

int64_t mix(input_type &sequence, size_t const nr_times = 1U,
            int64_t const key = 1U) {
    const size_t n = sequence.size();

    size_t i, j;

    for (size_t _{0}; _ < nr_times; ++_) {
        for (i = 0U; i < n; ++i) {
            for (j = 0U; j < n; ++j) {
                if (get<0>(sequence.at(j)) == i) {
                    break;
                }
            }

            auto val = get<1>(sequence.at(j));
            sequence.erase(
                std::next(sequence.begin(), static_cast<int64_t>(j)));
            int64_t kj = (static_cast<int64_t>(j) + val * key) %
                         (static_cast<int64_t>(n) - 1);
            j = (kj < 0) ? n + static_cast<size_t>(kj - 1)
                         : static_cast<size_t>(kj);
            sequence.insert(
                std::next(sequence.begin(), static_cast<int64_t>(j)), {i, val});
        }
    }
    for (i = 0U; i < n; ++i) {
        if (get<1>(sequence.at(i)) == 0U) {
            break;
        }
    }
    return key * get<1>(sequence.at((i + 1000) % n)) +
           key * get<1>(sequence.at((i + 2000) % n)) +
           key * get<1>(sequence.at((i + 3000) % n));
}
std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(mix(input));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return to_string(mix(input, 10, 811589153));
}

}  // namespace day20

}  // namespace year2022
