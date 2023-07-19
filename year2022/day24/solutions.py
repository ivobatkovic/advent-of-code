#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    rows = input_.splitlines()

    # Inner grid sizes
    height, width = len(rows) - 2, len(rows[0]) - 2

    # Make inner grid top left corner to be (0,0) instead of (1,1)
    grid, blizzards = set(), set()
    for y, row in enumerate(rows):
        for x, char in enumerate(row):
            if char == "#":
                grid.add((y - 1, x - 1))
            if char == ">":
                blizzards.add((y - 1, x - 1, 0, 1))
            if char == "<":
                blizzards.add((y - 1, x - 1, 0, -1))
            if char == "v":
                blizzards.add((y - 1, x - 1, 1, 0))
            if char == "^":
                blizzards.add((y - 1, x - 1, -1, 0))

    # Pad start and exit
    grid |= {(-2, 0), (height + 1, width - 1)}
    return grid, blizzards, height, width


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def traverse_grid(grid, blizzards, height, width, start, checkpoints):
    t = 0
    q = {start}
    while checkpoints:
        t += 1
        blizzard_pos = {
            ((py + t * dy) % (height), (px + t * dx) % (width))
            for py, px, dy, dx in blizzards
        }
        new_pos = {
            (py + dy, px + dx)
            for dy, dx in ((1, 0), (0, 1), (-1, 0), (0, -1), (0, 0))
            for py, px in q
        }
        q = new_pos - blizzard_pos - grid
        if checkpoints[0] in q:
            q = {checkpoints.pop(0)}
    return t


def solve_part1(input_):
    grid, blizzards, height, width = transform_input(input_)
    start = (-1, 0)
    end = (height, width - 1)
    return traverse_grid(grid, blizzards, height, width, start, [end])


def solve_part2(input_):
    grid, blizzards, height, width = transform_input(input_)
    start = (-1, 0)
    end = (height, width - 1)
    return traverse_grid(
        grid, blizzards, height, width, start, [end, start, end]
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 24")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day24/data/input.txt",
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
    "input1, output1", [("year2022/day24/data/test_input0.txt", 18)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day24/data/test_input0.txt", 54)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
