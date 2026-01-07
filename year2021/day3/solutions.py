#!/usr/bin/env python3
import argparse
import operator
import pytest
import time


def transform_input(input_):
    output = []
    for line in input_.splitlines():
        output.append([int(x) for x in line])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    gamma = 0
    for i in range(len(inp[0])):
        gamma = (gamma << 1) | (
            1 if sum([x[i] for x in inp]) > len(inp) / 2 else 0
        )

    # Invert gamma
    mask = (1 << len(inp[0])) - 1
    epsilon = mask ^ gamma

    return gamma * epsilon


def compute_rating(numbers, op=operator.ge):
    for i in range(len(numbers[0])):

        if len(numbers) == 1:
            break

        look_for = (
            1
            if op(sum([1 for x in numbers if x[i] == 1]), len(numbers) / 2)
            else 0
        )
        numbers = [x for x in numbers if x[i] == look_for]
    return int("".join(str(bit) for bit in numbers[0]), 2)


def solve_part2(input_):
    inp = transform_input(input_)

    return compute_rating(inp) * compute_rating(inp, operator.lt)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2021 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2021/day3/data/input.txt",
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
    "input1, output1", [("year2021/day3/data/test_input0.txt", 198)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2021/day3/data/test_input0.txt", 230)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
