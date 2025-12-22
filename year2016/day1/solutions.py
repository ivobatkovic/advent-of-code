#!/usr/bin/env python3
import argparse
import pytest
import numpy as np
import time


def transform_input(input_):

    output = []
    for x in input_.strip().split(", "):
        output.append((x[0], int(x[1:])))
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    pos, direction = (0, 0), np.pi / 2.0

    for d, step in inp:
        direction += np.pi / 2.0 if d == "L" else -np.pi / 2.0
        pos = (
            pos[0] + step * int(np.cos(direction)),
            pos[1] + step * int(np.sin(direction)),
        )

    return np.sum(np.abs(pos))


def solve_part2(input_):
    inp = transform_input(input_)

    visited = set()

    pos, direction = (0, 0), np.pi / 2.0
    for d, step in inp:
        direction += np.pi / 2.0 if d == "L" else -np.pi / 2.0
        dx, dy = int(np.cos(direction)), int(np.sin(direction))
        for _ in range(step):
            if pos in visited:
                return np.sum(np.abs(pos))
            visited.add(pos)
            pos = (pos[0] + dx, pos[1] + dy)

    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2016 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2016/day1/data/input.txt",
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
    "input1, output1", [("year2016/day1/data/test_input0.txt", 12)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("year2016/day1/data/test_input1.txt", 4)])
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
