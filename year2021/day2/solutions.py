#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):

    output = []
    for line in input_.splitlines():
        direction, val = line.split()
        if direction == "forward":
            output.append([int(val), 0])
        if direction == "up":
            output.append([0, -int(val)])
        elif direction == "down":
            output.append([0, int(val)])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    pos = [0, 0]
    for dx, dy in inp:
        pos = pos[0] + dx, pos[1] + dy

    return pos[0] * abs(pos[1])


def solve_part2(input_):
    inp = transform_input(input_)
    pos = [0, 0]
    aim = 0
    for dx, dy in inp:
        if dx:
            pos = pos[0] + dx, pos[1] + aim * dx
        else:
            aim += dy

    return pos[0] * abs(pos[1])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2021 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2021/day2/data/input.txt",
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
    "input1, output1", [("year2021/day2/data/test_input0.txt", 150)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2021/day2/data/test_input0.txt", 900)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
