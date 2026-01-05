#!/usr/bin/env python3
import argparse
import re
import pytest
import time

from collections import defaultdict


def transform_input(input_):
    regex = re.compile("\\d+")
    output = []
    for line in input_.splitlines():
        output.append([int(x) for x in regex.findall(line)])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    claims = defaultdict(lambda: [])
    for claim, x, y, w, h in inp:
        for dx in range(w):
            for dy in range(h):
                claims[(x + dx, y + dy)].append(claim)
    return sum([1 for value in claims.values() if len(value) > 1])


def solve_part2(input_):
    inp = transform_input(input_)

    claims = defaultdict(lambda: [])
    claim_set = set()
    for claim, x, y, w, h in inp:
        claim_set.add(claim)
        for dx in range(w):
            for dy in range(h):
                claims[(x + dx, y + dy)].append(claim)

    overlap_set = set()
    for values in claims.values():
        if len(values) > 1:
            for claim in values:
                overlap_set.add(claim)

    return claim_set.difference(overlap_set).pop()


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2018 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2018/day3/data/input.txt",
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
    "input1, output1", [("year2018/day3/data/test_input0.txt", 4)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2018/day3/data/test_input0.txt", 3)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
