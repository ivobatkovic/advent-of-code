#include "year2022/day17/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day17 {

using namespace std;

class Rock {
   public:
    vector<size_t> shape_{};
    size_t pos_{};
    size_t height_{};
    Rock(vector<size_t> shape, size_t pos = 0b0010000)
        : shape_{shape}, pos_{pos}, height_{shape.size()} {}

    Rock shift(char jet) {
        vector<size_t> shape;
        auto op = [](size_t x, char direction) {
            return (direction == '<') ? x << 1 : x >> 1;
        };
        for (size_t i{0}; i < height_; ++i) {
            shape.push_back(op(shape_[i], jet));
        }
        return Rock(shape, op(pos_, jet));
    }

    bool is_overlapping(map<size_t, size_t> const &bitmasks, size_t row) {
        for (size_t i{0}; i < height_; ++i) {
            if (bitmasks.count(row + i) && shape_[i] & bitmasks.at(row + i)) {
                return true;
            }
        }
        return false;
    }

    bool is_shiftable(char direction) {
        size_t edge = (direction == '>') ? 0b0000001 : 0b1000000;
        for (size_t i{0U}; i < height_; ++i) {
            if (shape_[i] & edge) {
                return false;
            }
        }
        return true;
    }
};

using input_type = pair<vector<Rock>, string>;
static input_type transform_input(const string &input_string) {
    vector<Rock> rocks{Rock({0b0011110}),
                       Rock({0b0001000, 0b0011100, 0b0001000}),
                       Rock({0b0011100, 0b0000100, 0b0000100}),
                       Rock({0b0010000, 0b0010000, 0b0010000, 0b0010000}),
                       Rock({0b0011000, 0b0011000})};
    string jet = utils::split_string<string>(input_string, "\n")[0];
    return {rocks, jet};
}

size_t compute_height(vector<Rock> const &rocks, string const &jets,
                      size_t const number_of_rocks) {
    map<size_t, size_t> bitmasks{};
    map<tuple<size_t, size_t, size_t>, pair<size_t, size_t>> states{};

    size_t height = 0;
    size_t i_jet = 0;

    for (size_t i_rock{0}; i_rock < number_of_rocks; ++i_rock) {
        Rock rock = rocks[i_rock % rocks.size()];
        size_t y{0U};
        for (size_t steps{0}; steps < height + 4; ++steps) {
            y = height + 3 - steps;
            char jet = jets[i_jet % jets.size()];
            i_jet++;
            if (rock.is_shiftable(jet)) {
                Rock shifted = rock.shift(jet);
                if (!shifted.is_overlapping(bitmasks, y)) {
                    rock = shifted;
                }
            }
            if (y == 0 || rock.is_overlapping(bitmasks, y - 1)) {
                for (size_t i{0U}; i < rock.height_; ++i) {
                    if (bitmasks.count(y + i)) {
                        bitmasks[y + i] |= rock.shape_[i];
                    } else {
                        bitmasks[y + i] = rock.shape_[i];
                    }
                }
                break;
            }
        }

        height = std::max(height, y + rock.height_);
        auto state = std::make_tuple(i_jet % jets.size(), i_rock % rocks.size(),
                                     rock.pos_);

        if (states.count(state)) {
            auto &[prev_rock, prev_height] = states[state];
            size_t rcycle = i_rock - prev_rock;
            size_t hcycle = height - prev_height;
            size_t diff = number_of_rocks - i_rock - 1;
            auto dv = std::div(int64_t(diff), int64_t(rcycle));
            if (dv.rem == 0) {
                return hcycle * size_t(dv.quot) + height;
            }
        } else {
            states[state] = make_pair(i_rock, height);
        }
    }
    return height;
}

std::string solve_part1(const string &input_string) {
    auto [rocks, jets] = transform_input(input_string);
    return std::to_string(compute_height(rocks, jets, 2022));
}

std::string solve_part2(const string &input_string) {
    auto [rocks, jets] = transform_input(input_string);
    return std::to_string(compute_height(rocks, jets, 1e12));
}

}  // namespace day17

}  // namespace year2022
