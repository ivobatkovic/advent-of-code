#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):

    return [line.split() for line in input_.splitlines()]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def is_valid(words, part_two=False):

    seen = set()

    for word in words:

        if part_two:
            word = "".join(sorted(word))

        if word in seen:
            return False
        seen.add(word)
    return True


def solve_part1(input_):
    inp = transform_input(input_)

    return sum([is_valid(words) for words in inp])


def solve_part2(input_):
    inp = transform_input(input_)
    return sum([is_valid(words, part_two=True) for words in inp])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2017 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2017/day4/data/input.txt",
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
    "input1, output1", [("year2017/day4/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2017/day4/data/test_input1.txt", 3)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
