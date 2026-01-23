#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    return list(map(int, re.findall(r"\d+", input_)))


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def redistribute(memory):

    idx, val = max(enumerate(memory), key=lambda x: x[1])
    memory[idx] = 0
    n = len(memory)
    for i in range(val):
        memory[(idx + 1 + i) % n] += 1


def solve_part1(input_):
    memory = transform_input(input_)
    visited = set()
    count = 0

    while True:
        state = tuple(memory)
        if state in visited:
            return count

        visited.add(state)
        redistribute(memory)
        count += 1


def solve_part2(input_):
    memory = transform_input(input_)
    visited = set()

    while True:
        state = tuple(memory)
        if state in visited:
            revisit = tuple(memory)
            break

        visited.add(state)
        redistribute(memory)

    count = 0
    while True:
        redistribute(memory)
        count += 1
        if tuple(memory) == revisit:
            return count


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2017 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2017/day6/data/input.txt",
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
    "input1, output1", [("year2017/day6/data/test_input0.txt", 5)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2017/day6/data/test_input0.txt", 4)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
