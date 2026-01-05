#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    width, height = len(inp[0]), len(inp)

    px, py = 0, 0
    dx, dy = 3, 1
    output = 0

    while py < height:
        if inp[py][px] == "#":
            output += 1
        px, py = (px + dx) % width, py + dy

    return output


def solve_part2(input_):
    inp = transform_input(input_)

    width, height = len(inp[0]), len(inp)

    output = 1
    for dx, dy in [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]:
        px, py, num_trees = 0, 0, 0
        while py < height:
            if inp[py][px] == "#":
                num_trees += 1
            px, py = (px + dx) % width, py + dy
        output *= num_trees if num_trees > 0 else 1

    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2020 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2020/day3/data/input.txt",
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
    "input1, output1", [("year2020/day3/data/test_input0.txt", 7)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2020/day3/data/test_input0.txt", 336)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
