#!/usr/bin/env python3
import argparse
import pytest
import time
import re


def transform_input(input_):
    mp = dict()
    for row in input_.splitlines():
        coords = list(map(int, re.findall("\\d+", row)))
        for i in range(len(coords) // 2 - 1):
            x1, y1 = coords[2 * i], coords[2 * i + 1]
            x2, y2 = coords[2 * i + 2], coords[2 * i + 3]

            dx = 1 if x2 - x1 >= 0 else -1
            dy = 1 if y2 - y1 >= 0 else -1

            xk = x1
            mp[y1, xk] = 1
            while xk != x2:
                xk += dx
                mp[y1, xk] = 1

            yk = y1
            mp[yk, x1] = 1
            while yk != y2:
                yk += dy
                mp[yk, x1] = 1

    return mp


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    mp = transform_input(input_)
    max_y = max([y for y, _ in mp.keys()])

    n_sand = 0
    while True:
        sy, sx = 0, 500
        while True:
            if (sy + 1, sx) in mp:
                if (sy + 1, sx - 1) not in mp:
                    sy += 1
                    sx -= 1
                elif (sy + 1, sx + 1) not in mp:
                    sy += 1
                    sx += 1
                else:
                    mp[sy, sx] = 2
                    break
            else:
                sy += 1
            if sy > max_y:
                break
        if sy < max_y:
            n_sand += 1
        else:
            break
    return n_sand


def solve_part2(input_):
    mp = transform_input(input_)
    max_y = max([y for y, _ in mp.keys()]) + 2
    n_sand = 0
    while True:
        sy, sx = 0, 500
        while True:
            if (sy + 1, sx) in mp or sy + 1 == max_y:
                if (sy + 1, sx - 1) not in mp and sy + 1 < max_y:
                    sy += 1
                    sx -= 1
                elif (sy + 1, sx + 1) not in mp and sy + 1 < max_y:
                    sy += 1
                    sx += 1
                else:
                    mp[sy, sx] = 2
                    break
            else:
                sy += 1
        if sy == 0 and sx == 500:
            break
        n_sand += 1
    return n_sand + 1


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 14")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day14/data/input.txt",
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
    "input1, output1", [("year2022/day14/data/test_input0.txt", 24)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day14/data/test_input0.txt", 93)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
