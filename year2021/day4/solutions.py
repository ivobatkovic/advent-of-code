#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    regex = re.compile("\\d+")
    lines = input_.splitlines()

    numbers = [int(x) for x in regex.findall(lines[0])]

    bingo_boards = []
    for row in range(2, len(lines), 6):
        board = {}
        for sub_row in range(5):
            sub_row_numbers = regex.findall(lines[row + sub_row])
            for col, nr in enumerate(sub_row_numbers):
                board[int(nr)] = (sub_row, col)
        bingo_boards.append(board)

    return numbers, bingo_boards


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    numbers, bingo_boards = transform_input(input_)

    # Keep track of number of hits per row/column per board
    rows = [[0] * 5 for _ in range(len(bingo_boards))]
    columns = [[0] * 5 for _ in range(len(bingo_boards))]

    # Keep track of drawn numbers
    drawn_numbers = set()

    for number in numbers:
        drawn_numbers.add(number)

        for i, board in enumerate(bingo_boards):

            if number not in board:
                continue

            row_idx, col_idx = board[number]
            rows[i][row_idx] += 1
            columns[i][col_idx] += 1

            if rows[i][row_idx] == 5 or columns[i][col_idx] == 5:
                unmarked = sum(
                    [key for key in board.keys() if key not in drawn_numbers]
                )
                return unmarked * number

    return 0


def solve_part2(input_):
    numbers, bingo_boards = transform_input(input_)

    # Keep track of number of hits per row/column per board
    rows = [[0] * 5 for _ in range(len(bingo_boards))]
    columns = [[0] * 5 for _ in range(len(bingo_boards))]

    # Keep track of drawn numbers
    drawn_numbers = set()

    completed = [False] * len(bingo_boards)
    num_boards_to_complete = len(bingo_boards)

    for number in numbers:
        drawn_numbers.add(number)

        for i, board in enumerate(bingo_boards):

            if number not in board or completed[i]:
                continue

            row_idx, col_idx = board[number]
            rows[i][row_idx] += 1
            columns[i][col_idx] += 1

            if rows[i][row_idx] == 5 or columns[i][col_idx] == 5:
                completed[i] = True
                num_boards_to_complete -= 1

                if num_boards_to_complete == 0:
                    unmarked = sum(
                        [
                            key
                            for key in board.keys()
                            if key not in drawn_numbers
                        ]
                    )
                    return unmarked * number

    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2021 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2021/day4/data/input.txt",
        nargs="?",
        help="Path to data file",
    )
    return parser.parse_args()


def main():
    parser = parse_args()
    input_ = read_input(parser.file_name)

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1:.2f}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2:.2f}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("year2021/day4/data/test_input0.txt", 4512)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2021/day4/data/test_input0.txt", 1924)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
