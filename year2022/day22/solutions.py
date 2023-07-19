#!/usr/bin/env python3
import argparse
import pytest
import time
import re


def transform_input(input_):
    grid = dict()
    rows = input_.splitlines()
    for y, row in enumerate(rows[:-2]):
        for x, char in enumerate(row):
            if char in ".#":
                grid[(y, x)] = char
    instructions = re.findall("\\d+|R|L", rows[-1])
    return grid, instructions


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def wrap_part1(grid, y, x, direction):
    if direction == 0:
        return (y, min(key[1] for key in grid if key[0] == y)), 0
    elif direction == 1:
        return (min(key[0] for key in grid if key[1] == x), x), 1
    elif direction == 2:
        return (y, max(key[1] for key in grid if key[0] == y)), 2
    elif direction == 3:
        return (max(key[0] for key in grid if key[1] == x), x), 3
    return (y, x, direction)


# Hard coded for this specific cube layout
def wrap_part2(y, x, direction):  # noqa: max-complexity=14
    y_, x_ = y // 50, x // 50
    if direction == 0 and y_ == 0:
        return (149 - y, 99), 2
    elif direction == 0 and y_ == 1:
        return (49, y + 50), 3
    elif direction == 0 and y_ == 2:
        return (149 - y, 149), 2
    elif direction == 0 and y_ == 3:
        return (149, y - 100), 3
    elif direction == 2 and y_ == 0:
        return (149 - y, 0), 0
    elif direction == 2 and y_ == 1:
        return (100, y - 50), 1
    elif direction == 2 and y_ == 2:
        return (149 - y, 50), 0
    elif direction == 2 and y_ == 3:
        return (0, y - 100), 1
    elif direction == 1 and x_ == 0:
        return (0, x + 100), 1
    elif direction == 1 and x_ == 1:
        return (100 + x, 49), 2
    elif direction == 1 and x_ == 2:
        return (-50 + x, 99), 2
    elif direction == 3 and x_ == 0:
        return (50 + x, 50), 0
    elif direction == 3 and x_ == 1:
        return (100 + x, 0), 0
    else:
        return (199, x - 100), 3


def traverse_map(grid, instructions, part1=True):
    # Find start position at top row
    sy, sx = (
        0,
        min(
            [
                key[1]
                for key, value in grid.items()
                if key[0] == 0 and value == "."
            ]
        ),
    )

    # Left, Down, Up, Right
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    direction = 0

    for instr in instructions:
        if instr == "L":
            direction = (direction - 1) % 4
        elif instr == "R":
            direction = (direction + 1) % 4
        else:
            for _ in range(int(instr)):
                py = sy + directions[direction][0]
                px = sx + directions[direction][1]
                d = direction
                if (py, px) not in grid:
                    (py, px), d = (
                        wrap_part1(grid, py, px, direction)
                        if part1
                        else wrap_part2(py, px, direction)
                    )
                if grid[(py, px)] == ".":
                    sy, sx = py, px
                    direction = d
                else:
                    break

    return 1000 * (sy + 1) + 4 * (sx + 1) + direction


def solve_part1(input_):
    grid, instructions = transform_input(input_)
    return traverse_map(grid, instructions)


def solve_part2(input_):
    grid, instructions = transform_input(input_)
    return traverse_map(grid, instructions, part1=False)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 22")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day22/data/input.txt",
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
    "input1, output1", [("year2022/day22/data/test_input0.txt", 6032)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1
