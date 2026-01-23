#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):

    grid = {}
    start_pos = (0, 0)

    rows = input_.splitlines()
    for i, row in enumerate(rows):
        for j, char in enumerate(row):
            grid[(i, j)] = char
            if char == "^":
                start_pos = (i, j)
    return start_pos, grid, len(rows), len(rows[0])


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def traverse(pos, grid, num_cols, num_rows, part_two=False):

    directions = [(0, -1), (1, 0), (0, 1), (-1, 0)]

    (dx, dy), i = directions[0], 0
    visited = set()
    while 0 <= pos[0] < num_rows and 0 <= pos[1] < num_cols:

        state = (pos, dy, dx)
        if part_two and state in visited:
            return False
        visited.add(state)

        new_pos = (pos[0] + dy, pos[1] + dx)
        if new_pos in grid and grid[new_pos] == "#":
            i = (i + 1) % 4
            dx, dy = directions[i]
        else:
            grid[pos] = "X"
            pos = new_pos
    return True


def solve_part1(input_):
    pos, grid, num_rows, num_cols = transform_input(input_)

    traverse(pos, grid, num_cols, num_rows)
    return sum([1 for value in grid.values() if value == "X"])


def solve_part2(input_):

    pos, grid, num_rows, num_cols = transform_input(input_)
    traverse(pos, grid, num_rows, num_cols)
    output = 0

    # Loop only over the path we traversed
    for key in [key for key in grid.keys() if grid[key] == "X"]:
        grid[key] = "#"
        if not traverse(pos, grid, num_rows, num_cols, part_two=True):
            output += 1
        grid[key] = "X"

    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2024 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2024/day6/data/input.txt",
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
    "input1, output1", [("year2024/day6/data/test_input0.txt", 41)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2024/day6/data/test_input0.txt", 6)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
