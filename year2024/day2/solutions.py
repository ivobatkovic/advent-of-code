#!/usr/bin/env python3
import argparse
import numpy as np
import pytest
import time


def transform_input(input_):
    output = []
    for line in input_.splitlines():
        output.append([int(x) for x in line.split()])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def is_safe(x):
    diff = np.diff(x)
    return (
        np.all(np.abs(diff) <= 3)
        and np.all(np.abs(diff) >= 1)
        and (np.all(diff > 0) or np.all(diff < 0))
    )


def solve_part1(input_):
    inp = transform_input(input_)

    return sum([is_safe(report) for report in inp])


def solve_part2(input_):
    inp = transform_input(input_)

    output = 0
    for report in inp:
        if is_safe(report):
            output += 1
        else:
            for i in range(len(report)):
                if is_safe(report[0:i] + report[i + 1 :]):
                    output += 1
                    break
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2024 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2024/day2/data/input.txt",
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
    "input1, output1", [("year2024/day2/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2024/day2/data/test_input0.txt", 4)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
