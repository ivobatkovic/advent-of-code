#!/usr/bin/env python3
import argparse
import re
import pytest
import sys
import time

from collections import defaultdict


def transform_input(input_):

    regex = re.compile(r"\d+")
    return [
        tuple(map(int, regex.findall(line))) for line in input_.splitlines()
    ]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def manhattan(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def get_bounding_box(points):

    x, y = zip(*points)
    return min(x), max(x), min(y), max(y)


def get_closest_position(pos, points):

    min_distance = sys.maxsize

    output = None
    for point in points:
        dist = manhattan(pos, point)
        if dist < min_distance:
            output = point
            min_distance = dist
        elif dist == min_distance:
            output = None
    return output


def solve_part1(input_):
    points = transform_input(input_)

    minx, maxx, miny, maxy = get_bounding_box(points)

    count = defaultdict(int)
    for x in range(minx, maxx + 1):
        for y in range(miny, maxy + 1):
            point = get_closest_position((x, y), points)
            if point:
                count[point] = count[point] + 1

    return max(val for val in count.values())


def solve_part2(input_, distance=10000):
    points = transform_input(input_)

    minx, maxx, miny, maxy = get_bounding_box(points)

    output = 0
    for x in range(minx, maxx + 1):
        for y in range(miny, maxy + 1):
            output += (
                sum(manhattan((x, y), point) for point in points) <= distance
            )
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2018 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2018/day6/data/input.txt",
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
    "input1, output1", [("year2018/day6/data/test_input0.txt", 17)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2018/day6/data/test_input0.txt", 16)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2), 30) == output2
