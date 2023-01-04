#!/usr/bin/env python3
import argparse
import pytest
import time
import re


def transform_input(input_):

    sensors = []
    beacons = set()
    for row in input_.splitlines():
        x1, y1, x2, y2 = list(map(int, re.findall("-?\\d+", row)))
        sensors.append((y1, x1, abs(x2 - x1) + abs(y2 - y1)))
        beacons.add((y2, x2))
    return sensors, beacons


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_, y_line=2000000):
    sensors, beacons = transform_input(input_)

    intervals = []
    for y, x, dist in sensors:
        print(y, x)
        dx = dist - abs(y_line - y)
        if dx < 0:
            continue
        intervals.append([x - dx, x + dx])
    if not intervals:
        return 0

    left_interval = min(left for left, _ in intervals)
    right_interval = max(right for _, right in intervals)
    n_locations = right_interval - left_interval + 1
    print(left_interval, right_interval, n_locations)
    return n_locations - sum(
        1
        for y, x in beacons
        if y == y_line and x >= left_interval and x <= right_interval
    )


def solve_part2(input_, y_max=4000000):
    sensors, _ = transform_input(input_)

    # Brute force - smarter choice on y_line can be made by looking at sensors
    for y_line in range(y_max + 1):
        intervals = []
        for y, x, dist in sensors:
            dx = dist - abs(y_line - y)
            if dx < 0:
                continue
            intervals.append([x - dx, x + dx])
        intervals.sort(key=lambda x: x[0])

        intersections = []
        left, right = intervals[0]
        for ll, rr in intervals[1:]:
            if right + 1 >= ll:
                right = max(right, rr)
            else:
                intersections.append([left, right])
                left, right = ll, rr
        intersections.append([left, right])

        if len(intersections) > 1:
            return 4000000 * (intersections[0][-1] + 1) + y_line
    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 15")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day15/data/input.txt",
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
    "input1, output1", [("year2022/day15/data/test_input0.txt", 26)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1), y_line=10) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day15/data/test_input0.txt", 56000011)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2), y_max=20) == output2
