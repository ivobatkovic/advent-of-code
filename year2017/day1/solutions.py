#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return [int(x) for x in input_.strip()]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    inp_aug = inp + [inp[0]]
    return sum([inp[i] for i in range(len(inp)) if inp[i] == inp_aug[i + 1]])


def solve_part2(input_):
    inp = transform_input(input_)

    N = len(inp) // 2
    inp_aug = inp + inp[0 : len(inp) // 2]
    return sum([inp_aug[i] for i in range(len(inp)) if inp_aug[i] == inp_aug[i + N]])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2017 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2017/day1/data/input.txt",
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
        ("year2017/day1/data/test_input0.txt", 9),
        ("year2017/day1/data/test_input1.txt", 0),
    ],
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("year2017/day1/data/test_input2.txt", 4),
        ("year2017/day1/data/test_input3.txt", 6),
        ("year2017/day1/data/test_input4.txt", 0),
    ],
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
