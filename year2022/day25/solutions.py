#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


offsets = {"=": 0, "-": 1, "0": 2, "1": 3, "2": 4}


def to_decimal(snafu):
    if snafu:
        return to_decimal(snafu[:-1]) * 5 + offsets[snafu[-1]] - 2
    else:
        return 0


def to_snafu(decimal):
    if decimal:
        a, b = divmod(decimal + 2, 5)
        return to_snafu(a) + "=-012"[b]
    else:
        return ""


def solve_part1(input_):
    inp = transform_input(input_)
    return to_snafu(sum([to_decimal(x) for x in inp]))


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 25")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day25/data/input.txt",
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


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("year2022/day25/data/test_input0.txt", "2=-1=0")]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1
