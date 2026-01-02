#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):

    output = []

    for line in input_.splitlines():

        steps = []
        for instruction in line:

            if instruction == "U":
                steps.append((0, -1))
            elif instruction == "D":
                steps.append((0, 1))
            elif instruction == "L":
                steps.append((-1, 0))
            elif instruction == "R":
                steps.append((1, 0))
        output.append(steps)

    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    mapping = {
        (0, 0): "1",
        (1, 0): "2",
        (2, 0): "3",
        (0, 1): "4",
        (1, 1): "5",
        (2, 1): "6",
        (0, 2): "7",
        (1, 2): "8",
        (2, 2): "9",
    }

    output = ""
    pos = (1, 1)
    for entry in inp:
        for dx, dy in entry:
            new_pos = (pos[0] + dx, pos[1] + dy)
            if new_pos in mapping:
                pos = new_pos
        output += mapping[(pos[0], pos[1])]
    return output


def solve_part2(input_):
    inp = transform_input(input_)

    mapping = {
        (2, 0): "1",
        (1, 1): "2",
        (2, 1): "3",
        (3, 1): "4",
        (0, 2): "5",
        (1, 2): "6",
        (2, 2): "7",
        (3, 2): "8",
        (4, 2): "9",
        (1, 3): "A",
        (2, 3): "B",
        (3, 3): "C",
        (2, 4): "D",
    }

    output = ""
    pos = (0, 2)
    for entry in inp:
        for dx, dy in entry:
            new_pos = (pos[0] + dx, pos[1] + dy)
            if new_pos in mapping:
                pos = new_pos
        output += mapping[pos]
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2016 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2016/day2/data/input.txt",
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
    "input1, output1", [("year2016/day2/data/test_input0.txt", "1985")]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2016/day2/data/test_input0.txt", "5DB3")]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
