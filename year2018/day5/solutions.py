#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return [x for x in input_.strip()]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def collapse(polymer):

    stack = []

    for char in polymer:
        if stack and abs(ord(stack[-1]) - ord(char)) == 32:
            stack.pop()
        else:
            stack.append(char)
    return len(stack)


def solve_part1(input_):
    inp = transform_input(input_)

    return collapse(inp)


def solve_part2(input_):
    inp = transform_input(input_)

    return min(
        [
            collapse(c for c in inp if c.lower() != chr(x))
            for x in range(ord("a"), ord("z") + 1)
        ]
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2018 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2018/day5/data/input.txt",
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
    "input1, output1", [("year2018/day5/data/test_input0.txt", 10)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2018/day5/data/test_input0.txt", 4)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
