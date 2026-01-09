#include "year2024/day4/cpp/solutions.hpp"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2024 {

namespace day4 {

using namespace std;
using pos_type = pair<int32_t, int32_t>;
using input_type = unordered_map<pos_type, char>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    vector<string> lines = utils::split_string<string>(input_string, "\n");
    for (size_t i{0U}; i < lines.size(); ++i) {
        string const &line = lines.at(i);
        for (size_t j{0U}; j < line.size(); ++j) {
            output[{i, j}] = line.at(j);
        }
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    vector<pos_type> directions{{-1, 1}, {-1, 0}, {-1, -1}, {0, 1},
                                {0, -1}, {1, 1},  {1, 0},   {1, -1}};

    for (auto const &[key, value] : input) {
        if (value != 'X') {
            continue;
        }

        for (auto const &dir : directions) {
            string match = "";
            for (int32_t k{1}; k < 4; ++k) {
                pos_type const pos{key.first + k * dir.first,
                                   key.second + k * dir.second};
                match += (input.contains(pos)) ? input[pos] : ' ';
            }
            if (match == "MAS") {
                output++;
            }
        }
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    vector<pos_type> directions{{-1, 1}, {-1, -1}, {1, 1}, {1, -1}};
    vector<pos_type> center_pos{};

    for (auto const &[key, value] : input) {
        if (value != 'M') {
            continue;
        }

        for (auto const &dir : directions) {
            string match = "";
            for (int32_t k{1}; k < 3; ++k) {
                pos_type const pos{key.first + k * dir.first,
                                   key.second + k * dir.second};
                match += (input.contains(pos)) ? input[pos] : ' ';
            }
            if (match == "AS") {
                center_pos.push_back(
                    {key.first + dir.first, key.second + dir.second});
            }
        }
    }

    for (size_t i{0U}; i < center_pos.size() - 1U; ++i) {
        for (size_t j{i + 1U}; j < center_pos.size(); ++j) {
            if (center_pos.at(i) == center_pos.at(j)) {
                output++;
            }
        }
    }
    return to_string(output);
}

}  // namespace day4

}  // namespace year2024
