#!/usr/bin/env python3
import argparse
import pytest
import time
from collections import defaultdict


def transform_input(input_):
    return input_.rstrip()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def find_marker(message, length=4):
    d, left = defaultdict(lambda: 0), 0
    for right, x in enumerate(message):
        d[x] += 1
        if d[x] > 1:
            while True:
                d[message[left]] -= 1
                left += 1
                if message[left - 1] == message[right]:
                    break
        elif right + 1 - left == length:
            break
    return right + 1


def solve_part1(input_):
    inp = transform_input(input_)
    return find_marker(inp)


def solve_part2(input_):
    inp = transform_input(input_)
    return find_marker(inp, 14)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day6/data/input.txt",
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
    "input1, output1",
    [
        ("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 7),
        ("bvwbjplbgvbhsrlpgdmjqwftvncz", 5),
        ("nppdvjthqldpwncqszvftbrmjlhg", 6),
        ("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10),
        ("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11),
    ],
)
def testPart1(input1, output1):
    assert solve_part1(input1) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 19),
        ("bvwbjplbgvbhsrlpgdmjqwftvncz", 23),
        ("nppdvjthqldpwncqszvftbrmjlhg", 23),
        ("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29),
        ("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 26),
    ],
)
def testPart2(input2, output2):
    assert solve_part2(input2) == output2
