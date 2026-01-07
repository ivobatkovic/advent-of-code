#include "year2025/day4/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2025 {

namespace day4 {

using namespace std;
using pos_type = pair<int32_t, int32_t>;
using input_type = unordered_set<pos_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    auto const lines = utils::split_string<string>(input_string, "\n");
    for (size_t i{0U}; i < lines.size(); ++i) {
        string const &line = lines.at(i);
        for (size_t j{0U}; j < line.size(); ++j) {
            if (line.at(j) == '@') {
                output.insert({i, j});
            }
        }
    }
    return output;
}

static vector<pos_type> neighbors = {{-1, 1}, {-1, 0}, {-1, -1}, {0, 1},
                                     {0, -1}, {1, 1},  {1, 0},   {1, -1}};

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    for (auto const &key : input) {
        size_t num_neighbors = accumulate(
            neighbors.begin(), neighbors.end(), 0U,
            [&key, &input](size_t const acc, pos_type const &pos) {
                return acc + input.contains({key.first + pos.first,
                                             key.second + pos.second});
            });

        if (num_neighbors < 4) {
            output++;
        }
    }

    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    while (true) {
        vector<pos_type> keys_to_remove{};

        for (auto const &key : input) {
            size_t num_neighbors = accumulate(
                neighbors.begin(), neighbors.end(), 0U,
                [&key, &input](size_t const acc, pos_type const &pos) {
                    return acc + input.contains({key.first + pos.first,
                                                 key.second + pos.second});
                });

            if (num_neighbors < 4) {
                output++;
                keys_to_remove.push_back(key);
            }
        }

        if (keys_to_remove.size() == 0) {
            break;
        }

        for (auto key : keys_to_remove) {
            input.erase(key);
        }
    }

    return to_string(output);
}

}  // namespace day4

}  // namespace year2025
