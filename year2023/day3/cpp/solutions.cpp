#include "year2023/day3/cpp/solutions.hpp"

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

namespace year2023 {

namespace day3 {

using namespace std;

using position_type = pair<int32_t, int32_t>;
using positions_type = vector<position_type>;

using numbers_map = unordered_map<int32_t, vector<positions_type>>;
using inverted_numbers_map = unordered_map<position_type, int32_t>;

using symbols_map = unordered_map<position_type, char>;

using input_type = pair<numbers_map, symbols_map>;

static positions_type neighbors{
    make_pair(-1, -1), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, -1),
    make_pair(0, 1),   make_pair(1, -1), make_pair(1, 0),  make_pair(1, 1),
};

static input_type transform_input(const string &input_string) {
    auto const lines = utils::split_string<string>(input_string, "\n");

    boost::regex digits("\\d+");
    boost::regex non_digits("[^\\d|^\\.]");

    numbers_map numbers{};
    symbols_map symbols{};

    for (size_t i{0U}; i < lines.size(); ++i) {
        auto const &line = lines.at(i);
        boost::sregex_iterator const end{};

        // Look for numbers on the line
        boost::sregex_iterator it(line.begin(), line.end(), digits);
        for (; it != end; ++it) {
            size_t const pos = static_cast<size_t>(it->position());
            string const &match = it->str();

            positions_type positions{};
            for (size_t j{pos}; j < pos + match.size(); ++j) {
                positions.push_back({i, j});
            }
            numbers[stoi(match)].push_back(positions);
        }

        // Look for symbols on the line
        it = boost::sregex_iterator(line.begin(), line.end(), non_digits);
        for (; it != end; ++it) {
            symbols[{i, it->position()}] = it->str().at(0U);
        }
    }

    return {numbers, symbols};
}

bool are_positions_adjacent(positions_type const &positions,
                            symbols_map const &symbols) {
    for (auto const &[x, y] : positions) {
        for (auto const &[dx, dy] : neighbors) {
            if (symbols.contains({x + dx, y + dy})) {
                return true;
            }
        }
    }
    return false;
}

std::string solve_part1(const string &input_string) {
    auto const &[numbers, symbols] = transform_input(input_string);

    int32_t output{};

    for (auto const &[key, value] : numbers) {
        for (auto const &positions : value) {
            output += (are_positions_adjacent(positions, symbols)) ? key : 0;
        }
    }
    return to_string(output);
}

inverted_numbers_map invert_map(numbers_map const &digits) {
    inverted_numbers_map output{};

    for (auto const &[key, value] : digits) {
        for (auto const &positions : value) {
            for (auto const &pos : positions) {
                output[pos] = key;
            }
        }
    }
    return output;
}

int32_t get_gear_ratio(position_type const &pos,
                       inverted_numbers_map const &numbers) {
    unordered_set<int32_t> visited{};

    for (auto const &[dx, dy] : neighbors) {
        position_type new_pos{pos.first + dx, pos.second + dy};
        if (numbers.contains(new_pos)) {
            visited.insert(numbers.at(new_pos));
        }
    }

    if (visited.size() == 2) {
        int32_t result = 1;
        for (auto const &x : visited) {
            result *= x;
        }
        return result;
    }

    return 0;
}

std::string solve_part2(const string &input_string) {
    auto const &[numbers, symbol] = transform_input(input_string);

    auto const reverse_numbers = invert_map(numbers);

    int32_t output{};

    for (auto const &[key, value] : symbol) {
        if (value != '*') {
            continue;
        }
        output += get_gear_ratio(key, reverse_numbers);
    }
    return to_string(output);
}

}  // namespace day3

}  // namespace year2023
