#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def get_priority(char):

    if ord(char) > ord("a"):
        return ord(char) - ord("a") + 1
    return ord(char) - ord("A") + 27


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for line in inp:
        N = len(line) // 2
        for char in set(line[0:N]).intersection(set(line[N:])):
            output += get_priority(char)

    return output


def solve_part2(input_):
    inp = transform_input(input_)

    output = 0
    for i in range(len(inp) // 3):
        for char in (
            set(inp[3 * i])
            .intersection(set(inp[3 * i + 1]))
            .intersection(set(inp[3 * i + 2]))
        ):
            output += get_priority(char)
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day3/data/input.txt",
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
    "input1, output1", [("year2022/day3/data/test_input0.txt", 157)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day3/data/test_input0.txt", 70)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
