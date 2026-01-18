#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    ranges_str, ingredients_str = input_.split("\n\n")

    regex = re.compile(r"\d+")

    ranges = []
    for range_ in ranges_str.splitlines():
        ranges.append(list(map(int, regex.findall(range_))))

    ingredients = list(map(int, ingredients_str.splitlines()))

    return ranges, ingredients


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def is_ingredient_in_ranges(ingredient, ranges):
    for lo, hi in ranges:

        if lo <= ingredient and ingredient <= hi:
            return True
    return False


def solve_part1(input_):
    ranges, ingredients = transform_input(input_)

    output = 0
    for ingredient in ingredients:
        output += is_ingredient_in_ranges(ingredient, ranges)

    return output


def propagate_ranges(ranges):

    ranges.sort()
    output = [ranges[0]]

    for lo, hi in ranges[1:]:
        if output[-1][1] < lo:
            output.append([lo, hi])
        else:
            output[-1][1] = max(output[-1][1], hi)

    return output


def solve_part2(input_):
    ranges, _ = transform_input(input_)
    return sum([hi - lo + 1 for lo, hi in propagate_ranges(ranges)])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2025 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2025/day5/data/input.txt",
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
    "input1, output1", [("year2025/day5/data/test_input0.txt", 3)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2025/day5/data/test_input0.txt", 14)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
