#include "year2022/day23/cpp/solutions.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day23 {

using namespace std;
using input_type = set<pair<int, int>>;

static input_type transform_input(const string &input_string) {
    input_type elves{};

    auto rows = utils::split_string<string>(input_string, "\n");
    for (size_t y = 0; y < rows.size(); ++y) {
        for (size_t x = 0; x < rows.at(y).size(); ++x) {
            if (rows.at(y).at(x) == '#') {
                elves.insert({y, x});
            }
        }
    }
    return elves;
}

bool propose_move(pair<int, int> const &elf, input_type const &elves) {
    auto &[y, x] = elf;
    return (elves.count({y - 1, x - 1}) || elves.count({y - 1, x}) ||
            elves.count({y - 1, x + 1}) || elves.count({y, x - 1}) ||
            elves.count({y, x + 1}) || elves.count({y + 1, x - 1}) ||
            elves.count({y + 1, x}) || elves.count({y + 1, x + 1}));
}

pair<int, int> get_proposal(pair<int, int> const &elf, input_type const &elves,
                            int direction) {
    auto &[y, x] = elf;
    for (int i = 0; i < 4; ++i) {
        if ((direction + i) % 4 == 0) {
            if (!elves.count({y - 1, x - 1}) && !elves.count({y - 1, x}) &&
                !elves.count({y - 1, x + 1}))
                return {y - 1, x};

        } else if ((direction + i) % 4 == 1) {
            if (!elves.count({y + 1, x - 1}) && !elves.count({y + 1, x}) &&
                !elves.count({y + 1, x + 1}))
                return {y + 1, x};
        } else if ((direction + i) % 4 == 2) {
            if (!elves.count({y - 1, x - 1}) && !elves.count({y, x - 1}) &&
                !elves.count({y + 1, x - 1}))
                return {y, x - 1};
        } else {
            if (!elves.count({y - 1, x + 1}) && !elves.count({y, x + 1}) &&
                !elves.count({y + 1, x + 1}))
                return {y, x + 1};
        }
    }
    return elf;
}

string move_elves(input_type &elves, bool part1 = true) {
    int direction = 0;
    int rounds = 0;

    while (true) {
        rounds++;

        // Generate movement proposals
        map<pair<int, int>, size_t> proposed_moves{};
        for (auto &elf : elves) {
            if (propose_move(elf, elves)) {
                auto [yp, xp] = get_proposal(elf, elves, direction);
                if (proposed_moves.count({yp, xp})) {
                    proposed_moves.at({yp, xp})++;
                } else {
                    proposed_moves[{yp, xp}] = 1;
                }
            }
        }

        if (proposed_moves.size() == 0) {
            return to_string(rounds);
        }

        // Check movement proposals
        input_type elves_{};
        for (auto &elf : elves) {
            if (propose_move(elf, elves)) {
                auto [yp, xp] = get_proposal(elf, elves, direction);
                if (proposed_moves.at({yp, xp}) == 1) {
                    elves_.insert({yp, xp});
                } else {
                    elves_.insert(elf);
                }
            } else {
                elves_.insert(elf);
            }
        }
        direction++;
        elves = elves_;
        if (part1 && rounds == 10) break;
    }

    vector<int> x_values;
    vector<int> y_values;
    for (const auto &point : elves) {
        y_values.push_back(point.first);
        x_values.push_back(point.second);
    }

    return to_string((*max_element(x_values.begin(), x_values.end()) + 1 -
                      *min_element(x_values.begin(), x_values.end())) *
                         (*max_element(y_values.begin(), y_values.end()) + 1 -
                          *min_element(y_values.begin(), y_values.end())) -
                     static_cast<int>(elves.size()));
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    return move_elves(input);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return move_elves(input, false);
}

}  // namespace day23

}  // namespace year2022
