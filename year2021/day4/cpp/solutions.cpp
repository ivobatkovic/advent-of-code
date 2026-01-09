#include "year2021/day4/cpp/solutions.hpp"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2021 {

namespace day4 {

using namespace std;

using row_type = array<size_t, 5U>;
using board_type = unordered_map<size_t, pair<size_t, size_t>>;
using bingo_boards_type = vector<board_type>;
using draw_numbers_type = vector<size_t>;

using input_type = pair<draw_numbers_type, bingo_boards_type>;

static input_type transform_input(const string &input_string) {
    vector<string> lines = utils::split_string<string>(input_string, "\n");

    boost::regex const regex("\\d+");
    draw_numbers_type numbers =
        utils::regex_find_all<size_t>(lines.front(), regex);

    bingo_boards_type bingo_boards{};
    for (size_t row{2U}; row < lines.size(); row += 6) {
        board_type board{};
        for (size_t sub_row{0U}; sub_row < 5; ++sub_row) {
            auto const sub_row_numbers =
                utils::regex_find_all<size_t>(lines.at(row + sub_row), regex);
            for (size_t col{0U}; col < 5; ++col) {
                board[sub_row_numbers.at(col)] = {sub_row, col};
            }
        }
        bingo_boards.push_back(board);
    }
    return make_pair(numbers, bingo_boards);
}

std::string solve_part1(const string &input_string) {
    auto const &[numbers, bingo_boards] = transform_input(input_string);

    // Keep track of number of hits per column/row per board
    vector<row_type> columns(bingo_boards.size(), row_type{});
    vector<row_type> rows(bingo_boards.size(), row_type{});

    // Keep track of which numbers have been drawn so far
    set<size_t> drawn_numbers{};

    for (auto const &number : numbers) {
        drawn_numbers.insert(number);

        for (size_t i{0U}; i < bingo_boards.size(); ++i) {
            auto const &board = bingo_boards.at(i);
            auto &col = columns.at(i);
            auto &row = rows.at(i);

            if (!board.contains(number)) {
                continue;
            }

            auto const &[row_index, col_index] = board.at(number);

            if (++col.at(col_index) == 5 || ++row.at(row_index) == 5) {
                size_t unmarked{};
                for (auto const &[key, value] : board) {
                    if (!drawn_numbers.contains(key)) {
                        unmarked += key;
                    }
                }

                return to_string(unmarked * number);
            }
        }
    }
    return "0";
}

std::string solve_part2(const string &input_string) {
    auto const &[numbers, bingo_boards] = transform_input(input_string);

    // Keep track of number of hits per column/row per board
    vector<row_type> columns(bingo_boards.size(), row_type{});
    vector<row_type> rows(bingo_boards.size(), row_type{});

    // Keep track of which numbers have been drawn so far
    set<size_t> drawn_numbers{};

    // Keep track of which boards are completed and how many should be completed
    vector<bool> completed(bingo_boards.size(), false);
    size_t num_boards_to_complete = bingo_boards.size();

    for (auto const &number : numbers) {
        drawn_numbers.insert(number);

        for (size_t i{0U}; i < bingo_boards.size(); ++i) {
            auto const &board = bingo_boards.at(i);

            if (completed.at(i) || !board.contains(number)) {
                continue;
            }

            auto &col = columns.at(i);
            auto &row = rows.at(i);
            auto const &[row_index, col_index] = board.at(number);

            if (++col.at(col_index) == 5 || ++row.at(row_index) == 5) {
                completed.at(i) = true;

                if (--num_boards_to_complete == 0) {
                    size_t unmarked{};
                    for (auto const &[key, value] : board) {
                        if (!drawn_numbers.contains(key)) {
                            unmarked += key;
                        }
                    }

                    return to_string(unmarked * number);
                }
            }
        }
    }
    return "0";
}

}  // namespace day4

}  // namespace year2021
