#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return [list(map(int, x)) for x in input_.splitlines()]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def compute_visibility(heights, inp, dx, dy):

    if dx:
        for row in range(len(inp)):
            start = 0 if dx > 0 else len(inp[row]) - 1
            val = -1
            while start > -1 and start < len(inp[row]):
                if val < inp[row][start]:
                    heights[row, start] = 1
                    val = inp[row][start]
                if val == 9:
                    break
                start += dx
    else:
        for col in range(len(inp[0])):
            start = 0 if dy > 0 else len(inp) - 1
            val = -1
            while start > -1 and start < len(inp):
                if val < inp[start][col]:
                    heights[start, col] = 1
                    val = inp[start][col]
                if val == 9:
                    break
                start += dy


def solve_part1(input_):
    inp = transform_input(input_)

    heights = dict()
    for dx, dy in ((-1, 0), (1, 0), (0, 1), (0, -1)):
        compute_visibility(heights, inp, dx, dy)
    return sum(x for x in heights.values())


def compute_scenic_score(height, inp, row, col):
    total = 1
    for dx, dy in ((-1, 0), (1, 0), (0, 1), (0, -1)):
        count = 1
        if dx:
            k = col + dx
            while (
                k > 0 and k < len(inp[0]) - 1 and inp[row][col] > inp[row][k]
            ):
                count += 1
                k += dx
            total *= count
        else:
            k = row + dy
            while k > 0 and k < len(inp) - 1 and inp[row][col] > inp[k][col]:
                count += 1
                k += dy
            total *= count
    height[row, col] = total


def solve_part2(input_):
    inp = transform_input(input_)

    height = dict()

    for row in range(1, len(inp) - 1):
        for col in range(1, len(inp[0]) - 1):
            compute_scenic_score(height, inp, row, col)

    return max(x for x in height.values())


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 8")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day8/data/input.txt",
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
    "input1, output1", [("year2022/day8/data/test_input0.txt", 21)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day8/data/test_input0.txt", 8)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
