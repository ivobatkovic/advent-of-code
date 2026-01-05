#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):

    left, mid, right = [], [], []
    for line in input_.splitlines():
        x = [int(x) for x in line.split()]
        left.append(x[0])
        mid.append(x[1])
        right.append(x[2])
    return left, mid, right


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for x in zip(*inp):
        a, b, c = sorted(x)
        if a + b > c:
            output += 1
    return output


def solve_part2(input_):
    left, mid, right = transform_input(input_)

    def check_triangles(triangles):
        output = 0
        num_triangles = len(triangles) // 3
        for i in range(num_triangles):
            a, b, c = sorted(triangles[i * 3 : i * 3 + 3])
            if a + b > c:
                output += 1
        return output

    return sum([check_triangles(triangle) for triangle in [left, mid, right]])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2016 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2016/day3/data/input.txt",
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
    "input1, output1", [("year2016/day3/data/test_input0.txt", 0)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2016/day3/data/test_input1.txt", 6)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
