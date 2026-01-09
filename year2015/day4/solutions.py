#!/usr/bin/env python3
import argparse
import hashlib
import pytest
import time


def transform_input(input_):
    return input_.strip()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def check_md5(key, part_two=False):
    md5_hash = hashlib.md5(key.encode()).digest()
    if part_two:
        return md5_hash[0] == 0 and md5_hash[1] == 0 and md5_hash[2] == 0
    return (
        md5_hash[0] == 0 and md5_hash[1] == 0 and md5_hash[2] & 0b11110000 == 0
    )


def solve_part1(input_, num=0):
    key = transform_input(input_)

    while True:
        if check_md5(key + str(num)):
            return num
        num += 1


def solve_part2(input_, num=0):
    key = transform_input(input_)
    while True:
        if check_md5(key + str(num), part_two=True):
            return num
        num += 1


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2015 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2015/day4/data/input.txt",
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
    "input1, output1", [("year2015/day4/data/test_input0.txt", 609043)]
)
def testPart1(input1, output1):
    # Kick start the solution to avoid unecessary brute force
    assert solve_part1(read_input(input1), num=0) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2015/day4/data/test_input0.txt", 6742839)]
)
def testPart2(input2, output2):
    # Kick start the solution to avoid unecessary brute force
    assert solve_part2(read_input(input2), num=6742830) == output2
