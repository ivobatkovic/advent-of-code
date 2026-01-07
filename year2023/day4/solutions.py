#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    output = []

    regex = re.compile("\\d+")
    for line in input_.splitlines():
        left, right = line.split("|")
        output.append(
            [
                [int(x) for x in regex.findall(left)][1:],
                [int(x) for x in regex.findall(right)],
            ]
        )
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for winning, cards in inp:
        num_matching = len(set(winning).intersection(set(cards)))
        if num_matching:
            output += 2 ** (num_matching - 1)
    return output


def solve_part2(input_):
    inp = transform_input(input_)

    instances = [0] * len(inp)
    for i, (winning, cards) in enumerate(inp):
        num_matching = len(set(winning).intersection(set(cards)))

        instances[i] += 1
        if num_matching:
            for k in range(num_matching):
                instances[i + (k + 1)] += instances[i]
    return sum([val for val in instances])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2023 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2023/day4/data/input.txt",
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
    "input1, output1", [("year2023/day4/data/test_input0.txt", 13)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2023/day4/data/test_input0.txt", 30)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
