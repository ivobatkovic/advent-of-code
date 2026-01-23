#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    return list(map(int, re.findall(r"\d", input_.strip())))


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def cycle(start_count, days):

    fish = [0] * 9
    for nr in start_count:
        fish[nr] += 1

    for _ in range(days):
        fish_tmp = [0] * 9
        for i in range(8, 0, -1):
            fish_tmp[i - 1] = fish[i]
        fish_tmp[6] += fish[0]
        fish_tmp[8] = fish[0]
        fish = fish_tmp
    return sum(fish)


def solve_part1(input_):
    inp = transform_input(input_)
    return cycle(inp, 80)


def solve_part2(input_):
    inp = transform_input(input_)
    return cycle(inp, 256)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2021 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2021/day6/data/input.txt",
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
    "input1, output1", [("year2021/day6/data/test_input0.txt", 5934)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2021/day6/data/test_input0.txt", 26984457539)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
