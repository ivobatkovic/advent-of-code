#include "year2017/day3/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

template <>
struct std::hash<std::pair<int32_t, int32_t>> {
    size_t operator()(const pair<int32_t, int32_t> &p) const {
        return hash<int32_t>{}(p.first) * 31 + hash<int32_t>{}(p.second);
    }
};

namespace year2017 {

namespace day3 {

using namespace std;
using input_type = vector<int32_t>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<int32_t>(input_string, "\n");
}

pair<int32_t, int32_t> find_layer_and_start_value(int32_t const digit) {
    int32_t layer{};
    int32_t value = 1;

    while (true) {
        int32_t N = 1 + 2 * layer;
        if ((digit > value + 1) && (digit < (value + 4 * N - 4))) {
            return make_pair(value + 1, layer);
        }
        value += 4 * N - 4;
        layer++;
    }
    return make_pair(0, 0);
}

int32_t get_manhattan_distance(int32_t const digit) {
    if (digit == 1) {
        return 0;
    }

    auto const &[value, layer] = find_layer_and_start_value(digit);

    pair<int32_t, int32_t> pos{layer, 1 - layer};
    int32_t diff = digit - value;

    // Number of elements in the layer
    int32_t N = 1 + 2 * layer;

    if (diff <= (N - 2)) {
        pos.second += diff;
    } else if (diff <= (2 * N - 3)) {
        diff -= N - 2;
        pos.first -= diff;
        pos.second += N - 2;
    } else if (diff <= (3 * N - 4)) {
        diff -= 2 * N - 3;
        pos.first -= N - 1;
        pos.second += N - 2 - diff;
    } else {
        diff -= 3 * N - 4;
        pos.first += -(N - 1) + diff;
        pos.second -= 1;
    }
    return abs(pos.first) + abs(pos.second);
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(
        accumulate(input.begin(), input.end(), 0, [](int32_t acc, int32_t x) {
            return acc + get_manhattan_distance(x);
        }));
}

int32_t find_value(int32_t const digit) {
    array<pair<int32_t, int32_t>, 8U> neighbors{
        make_pair(-1, 1), make_pair(-1, 0), make_pair(-1, -1), make_pair(0, 1),
        make_pair(0, -1), make_pair(1, 1),  make_pair(1, 0),   make_pair(1, -1),
    };

    unordered_map<pair<int32_t, int32_t>, int32_t> table{{make_pair(0, 0), 1}};

    pair<int32_t, int32_t> pos{1, 0};
    int32_t layer{1};

    while (true) {
        int32_t N = 1 + 2 * layer;

        // Loop over the elements of each layer in the spiral
        for (int32_t k{1}; k < 4 * N - 4 + 1; ++k) {
            int32_t val = accumulate(
                neighbors.begin(), neighbors.end(), 0,
                [&table, &pos](int32_t acc, pair<int32_t, int32_t> const &x) {
                    auto [dx, dy] = x;
                    auto new_pos = make_pair(pos.first + dx, pos.second + dy);
                    return (table.contains(new_pos)) ? acc + table[new_pos]
                                                     : acc;
                });

            table[pos] = val;

            if (val > digit) {
                return val;
            }

            if (k <= N - 2) {
                pos.second += 1;
            } else if (k <= 2 * N - 3) {
                pos.first -= 1;
            } else if (k <= 3 * N - 4) {
                pos.second -= 1;
            } else {
                pos.first += 1;
            }
        }
        layer++;
    }
    return 0;
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(
        accumulate(input.begin(), input.end(), 0,
                   [](int32_t acc, int32_t x) { return acc + find_value(x); }));
}

}  // namespace day3

}  // namespace year2017
