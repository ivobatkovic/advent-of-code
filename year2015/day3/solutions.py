#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):

    output = []
    for char in input_:
        if char == ">":
            output.append((1, 0))
        elif char == "<":
            output.append((-1, 0))
        elif char == "^":
            output.append((0, 1))
        elif char == "v":
            output.append((0, -1))
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def visited_houses(steps, visited, pos=(0, 0)):
    visited.add(pos)
    for dx, dy in steps:
        pos = pos[0] + dx, pos[1] + dy
        visited.add(pos)
    return len(visited)


def solve_part1(input_):
    inp = transform_input(input_)

    return visited_houses(inp, set())


def solve_part2(input_):
    inp = transform_input(input_)

    visited = set()
    visited_houses(inp[0::2], visited)
    return visited_houses(inp[1::2], visited)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2015 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2015/day3/data/input.txt",
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
    "input1, output1", [("year2015/day3/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2015/day3/data/test_input0.txt", 11)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
