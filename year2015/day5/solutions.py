#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    vowels = re.compile("(?:[aeiou].*){3,}")
    double = re.compile("(.)\\1")
    forbidden = re.compile("ab|cd|pq|xy")

    def is_nice(word):
        has_vowels = vowels.search(word) is not None
        has_double = double.search(word) is not None
        has_forbidden = forbidden.search(word) is not None

        return has_vowels and has_double and not has_forbidden

    return sum([is_nice(word) for word in inp])


def solve_part2(input_):
    inp = transform_input(input_)

    non_overlapping_pair = re.compile("(..).*\\1")
    one_character_inbetween = re.compile("(.).\\1")

    def is_nice(word):
        has_non_overlapping_pair = (
            non_overlapping_pair.search(word) is not None
        )
        has_one_character_inbetween = (
            one_character_inbetween.search(word) is not None
        )
        return has_non_overlapping_pair and has_one_character_inbetween

    return sum([is_nice(word) for word in inp])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2015 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2015/day5/data/input.txt",
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
    "input1, output1", [("year2015/day5/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2015/day5/data/test_input1.txt", 2)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
