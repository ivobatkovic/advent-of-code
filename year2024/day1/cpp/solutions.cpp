#include "year2024/day1/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2024 {

namespace day1 {

using namespace std;
using input_type = pair<vector<int64_t>, vector<int64_t>>;

static input_type transform_input(const string &input_string) {
    static_cast<void>(input_string);

    vector<int64_t> L{}, R{};

    for (auto &line : utils::split_string<string>(input_string, "\n")) {
        auto match = utils::regex_find_all<int64_t>(line, boost::regex("\\d+"));
        L.push_back(match.front());
        R.push_back(match.back());
    }
    return std::make_pair(L, R);
}

std::string solve_part1(const string &input_string) {
    auto [L, R] = transform_input(input_string);

    sort(L.begin(), L.end());
    sort(R.begin(), R.end());
    vector<int64_t> diff(L.size());

    transform(L.begin(), L.end(), R.begin(), diff.begin(),
              [](int64_t l, int64_t r) { return abs(l - r); });

    return to_string(accumulate(diff.begin(), diff.end(), 0));
}

std::string solve_part2(const string &input_string) {
    auto const [L, R] = transform_input(input_string);

    unordered_map<int64_t, int64_t> occurence{};
    for (auto &r : R) {
        if (occurence.contains(r)) {
            occurence[r]++;
        } else {
            occurence[r] = 1;
        }
    }

    return to_string(
        accumulate(L.begin(), L.end(), 0, [&occurence](int64_t acc, int64_t x) {
            return acc + x * occurence[x];
        }));
}

}  // namespace day1

}  // namespace year2024
