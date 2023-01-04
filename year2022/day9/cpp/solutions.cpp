#include "year2022/day9/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day9 {

using namespace std;
using input_type = vector<array<int, 3U>>;
using map_type = map<pair<int, int>, size_t>;

static input_type transform_input(const string &input_string) {
    input_type output{};
    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto left_right = utils::split_string<string>(row, " ");
        int dx = (left_right[0] == "R") ? 1 : (left_right[0] == "L") ? -1 : 0;
        int dy = (left_right[0] == "U") ? 1 : (left_right[0] == "D") ? -1 : 0;
        output.push_back({dx, dy, stoi(left_right[1])});
    }
    return output;
}

class Rope {
   public:
    Rope(int knots) {
        tail_ = (knots > 0) ? make_unique<Rope>(knots - 1) : nullptr;
    }

    void update(int dx, int dy, map_type &mp) {
        row_ += dy;
        col_ += dx;

        if (tail_ != nullptr) {
            bool cond_row = abs(row_ - tail_->row_) > 1;
            bool cond_col = abs(col_ - tail_->col_) > 1;
            if (cond_row || cond_col) {
                if (cond_row) {
                    dy = (row_ > tail_->row_) ? 1 : -1;
                    dx = min(max(col_ - tail_->col_, -1), 1);
                } else if (cond_col) {
                    dx = (col_ > tail_->col_) ? 1 : -1;
                    dy = min(max(row_ - tail_->row_, -1), 1);
                }
                tail_->update(dx, dy, mp);
            }
        } else {
            mp[make_pair(row_, col_)] = 1U;
        }
    }

    unique_ptr<Rope> tail_{};
    int row_{};
    int col_{};
};

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    map_type mp{};
    mp[make_pair(0, 0)] = 1U;

    Rope rope(1);

    for (auto &[dx, dy, step] : input) {
        for (int i{0}; i < step; ++i) {
            rope.update(dx, dy, mp);
        }
    }
    return to_string(mp.size());
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    map_type mp{};
    mp[make_pair(0, 0)] = 1U;

    Rope rope(9);

    for (auto &[dx, dy, step] : input) {
        for (int i{0}; i < step; ++i) {
            rope.update(dx, dy, mp);
        }
    }
    return to_string(mp.size());
}

}  // namespace day9

}  // namespace year2022
