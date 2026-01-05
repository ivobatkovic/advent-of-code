#include "year2018/day3/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2018 {

namespace day3 {

using namespace std;
using input_type = vector<array<int32_t, 5U>>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const numbers =
            utils::regex_find_all<int32_t>(line, boost::regex("\\d+"));
        assert(numbers.size() == 5U);
        output.push_back({numbers.at(0U), numbers.at(1U), numbers.at(2U),
                          numbers.at(3U), numbers.at(4U)});
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    unordered_map<pair<int32_t, int32_t>, vector<int32_t>> claims{};

    for (auto const &[claim, x, y, w, h] : input) {
        for (int32_t dx{0U}; dx < w; ++dx) {
            for (int32_t dy{0U}; dy < h; ++dy) {
                pair<int32_t, int32_t> pos{x + dx, y + dy};
                claims[pos].push_back(claim);
            }
        }
    }
    return to_string(accumulate(
        claims.begin(), claims.end(), 0, [](int32_t acc, auto const &pair) {
            return (pair.second.size() > 1) ? acc + 1 : acc;
        }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    unordered_map<pair<int32_t, int32_t>, vector<int32_t>> claims{};
    unordered_set<int32_t> claims_set{};

    for (auto const &[claim, x, y, w, h] : input) {
        claims_set.insert(claim);
        for (int32_t dx{0U}; dx < w; ++dx) {
            for (int32_t dy{0U}; dy < h; ++dy) {
                pair<int32_t, int32_t> pos{x + dx, y + dy};
                claims[pos].push_back(claim);
            }
        }
    }

    unordered_set<int32_t> overlap_set{};
    for (auto const &pair : claims) {
        if (pair.second.size() > 1) {
            for (int32_t const &claim : pair.second) {
                overlap_set.insert(claim);
            }
        }
    }

    for (auto const &claim : claims_set) {
        if (!overlap_set.count(claim)) {
            return to_string(claim);
        }
    }
    return "0";
}

}  // namespace day3

}  // namespace year2018
