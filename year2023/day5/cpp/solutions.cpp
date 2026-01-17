#include "year2023/day5/cpp/solutions.hpp"

#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int64_t, int64_t>> {
    size_t operator()(const pair<int64_t, int64_t> &p) const {
        return hash<int64_t>{}(p.first) * 31 + hash<int64_t>{}(p.second);
    }
};

namespace year2023 {

namespace day5 {

using namespace std;
using seeds_type = vector<int64_t>;
using range_type = pair<int64_t, int64_t>;
using mapping_type = unordered_map<range_type, int64_t>;
using mappings_type = vector<mapping_type>;
using input_type = pair<seeds_type, mappings_type>;

static input_type transform_input(const string &input_string) {
    auto const data = utils::split_string<string>(input_string, "\n\n");
    seeds_type seeds =
        utils::regex_find_all<int64_t>(data.front(), boost::regex("\\d+"));

    mappings_type mappings{};
    for (auto it = data.begin() + 1; it != data.end(); ++it) {
        mapping_type mapping{};
        vector<string> lines = utils::split_string<string>(*it, "\n");
        for (size_t i{1U}; i < lines.size(); ++i) {
            auto const numbers = utils::regex_find_all<int64_t>(
                lines.at(i), boost::regex("\\d+"));
            assert(numbers.size() == 3U);
            int64_t start_val = numbers.at(0U);
            int64_t start = numbers.at(1U);
            int64_t num = numbers.at(2U);
            mapping[make_pair(start, start + num - 1)] = start_val - start;
        }
        mappings.push_back(mapping);
    }

    return {seeds, mappings};
}

vector<range_type> propagate_ranges(vector<range_type> const &input_ranges,
                                    mapping_type const &mapping) {
    vector<range_type> output_ranges{};

    for (range_type const &range : input_ranges) {
        vector<range_type> ranges_to_check{range};
        for (auto const &[key, value] : mapping) {
            vector<range_type> new_ranges{};
            for (auto const &[lo, hi] : ranges_to_check) {
                if (hi < key.first || lo > key.second) {
                    new_ranges.push_back({lo, hi});
                    continue;
                }

                if (lo < key.first) {
                    new_ranges.push_back({lo, key.first - 1});
                }

                output_ranges.push_back(
                    {max(lo, key.first) + value, min(hi, key.second) + value});

                if (key.second < hi) {
                    new_ranges.push_back({key.second + 1, hi});
                }
            }
            ranges_to_check = new_ranges;
        }
        copy(ranges_to_check.begin(), ranges_to_check.end(),
             std::back_inserter(output_ranges));
    }
    return output_ranges;
}

std::string solve_part1(const string &input_string) {
    auto const &[seeds, mappings] = transform_input(input_string);

    vector<int64_t> output{};

    for (auto const &seed : seeds) {
        vector<range_type> ranges{{seed, seed}};
        for (auto const &mapping : mappings) {
            ranges = propagate_ranges(ranges, mapping);
        }

        output.push_back(std::min_element(ranges.begin(), ranges.end(),
                                          [](range_type a, range_type b) {
                                              return a.first < b.first;
                                          })
                             ->first);
    }
    return to_string(*std::min_element(output.begin(), output.end()));
}

std::string solve_part2(const string &input_string) {
    auto const &[seeds, mappings] = transform_input(input_string);

    vector<range_type> ranges{};
    for (size_t i{0U}; i < seeds.size(); i += 2) {
        ranges.push_back({seeds.at(i), seeds.at(i) + seeds.at(i + 1) - 1});
    }

    for (auto const &mapping : mappings) {
        ranges = propagate_ranges(ranges, mapping);
    }

    return to_string(
        std::min_element(ranges.begin(), ranges.end(),
                         [](range_type const &a, range_type const &b) {
                             return a.first < b.first;
                         })
            ->first);
}

}  // namespace day5

}  // namespace year2023
