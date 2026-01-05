#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = []
    for line in input_.splitlines():
        steps = []

        pos = (0, 0)
        for instruction in line.split(","):

            direction, step = instruction[0], int(instruction[1:])

            dx, dy = 0, 0
            if direction == "U":
                dy = step
            elif direction == "D":
                dy = -step
            elif direction == "L":
                dx = -step
            elif direction == "R":
                dx = step

            new_pos = pos[0] + dx, pos[1] + dy
            steps.append((pos[0], pos[1], new_pos[0], new_pos[1]))
            pos = new_pos
        output.append(steps)

    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def check_intersection(line_a, line_b):

    _, y1, _, y2 = line_a
    _, y3, _, y4 = line_b

    is_a_horizontal = y1 == y2
    is_b_horizontal = y3 == y4

    if is_a_horizontal != is_b_horizontal:

        hx1, hy, hx2, _ = line_a if is_a_horizontal else line_b
        vx, vy1, _, vy2 = line_b if is_a_horizontal else line_a

        if min(hx1, hx2) <= vx <= max(hx1, hx2) and min(vy1, vy2) <= hy <= max(
            vy1, vy2
        ):
            return True, (vx, hy)
    return False, (0, 0)


def solve_part1(input_):
    line1, line2 = transform_input(input_)

    output = []
    for seg1 in line1:
        for seg2 in line2:
            valid, pos = check_intersection(seg1, seg2)
            if valid and pos != (0, 0):
                output.append(abs(pos[0]) + abs(pos[1]))
    return min(output)


def solve_part2(input_):
    line1, line2 = transform_input(input_)
    output = []

    dist_seg1 = 0
    for seg1 in line1:
        dist_seg2 = 0
        for seg2 in line2:
            valid, pos = check_intersection(seg1, seg2)
            if valid and pos != (0, 0):
                output.append(
                    dist_seg1
                    + abs(seg1[0] - pos[0])
                    + abs(seg1[1] - pos[1])
                    + dist_seg2
                    + abs(seg2[0] - pos[0])
                    + abs(seg2[1] - pos[1])
                )
            dist_seg2 += abs(seg2[2] - seg2[0]) + abs(seg2[3] - seg2[1])
        dist_seg1 += abs(seg1[2] - seg1[0]) + abs(seg1[3] - seg1[1])

    return min(output)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2019 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2019/day3/data/input.txt",
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
        ("year2019/day3/data/test_input0.txt", 6),
        ("year2019/day3/data/test_input1.txt", 159),
        ("year2019/day3/data/test_input2.txt", 135),
    ],
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("year2019/day3/data/test_input0.txt", 30),
        ("year2019/day3/data/test_input1.txt", 610),
        ("year2019/day3/data/test_input2.txt", 410),
    ],
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
