#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = []
    for line in input_.splitlines():
        nr = int(line[1:])
        output.append(nr if line[0] == "R" else -nr)
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    x = 50
    output = 0
    for d in inp:
        x = (x + d) % 100
        if x == 0:
            output += 1
    return output


def solve_part2(input_):
    inp = transform_input(input_)

    x = 50
    output = 0
    for d in inp:

        # Normalize the steps around the dial
        output += abs(d) // 100
        d = d % 100 if d > 0 else d % 100 - 100

        x_next = (x + d) % 100

        if x_next == 0 or (
            x != 0 and (x_next > x and d < 0) or (x_next < x and d > 0)
        ):
            output += 1

        x = x_next

    return output


# 6228 TCORRECT


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2025 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2025/day1/data/input.txt",
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
    "input1, output1", [("year2025/day1/data/test_input0.txt", 3)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2025/day1/data/test_input0.txt", 6)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
