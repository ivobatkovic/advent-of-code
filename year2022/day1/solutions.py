#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    calories_per_elf = []
    calories = []
    for x in input_.splitlines():
        if x:
            calories.append(int(x))
        else:
            calories_per_elf.append(calories)
            calories = []
    calories_per_elf.append(calories)
    return calories_per_elf


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return max(sum(x for x in calories) for calories in inp)


def solve_part2(input_):
    inp = transform_input(input_)
    return sum(
        sorted([sum(x for x in calories) for calories in inp], reverse=True)[
            :3
        ]
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day1/data/input.txt",
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
    "input1, output1", [("year2022/day1/data/test_input0.txt", 24000)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day1/data/test_input0.txt", 45000)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
