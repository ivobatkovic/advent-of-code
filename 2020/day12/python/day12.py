#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
from math import pi, sin, cos

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day
    return [(inp[0], int(inp[1:])) for inp in input_.splitlines()]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):

    shift = {"N": [0, 1], "S": [0, -1], "W": [-1, 0], "E": [1, 0]}
    rotate = {"R": -pi / 180, "L": pi / 180}
    move = {"F": 1}

    pos, heading = [0, 0], 0
    for action, value in input_:
        # Update position in direction of heading
        if action in move:
            dxdy = [int(round(cos(heading))), int(round(sin(heading)))]
            pos = [p + value * d for p, d in zip(pos, dxdy)]
        # Shift action north/south/west/east
        elif action in shift:
            pos = [p + value * s for p, s in zip(pos, shift[action])]
        # Change direction left or right
        elif action in rotate:
            heading += rotate[action] * value
    return abs(pos[0]) + abs(pos[1])


def solve_part2(input_):

    shift = {"N": [0, 1], "S": [0, -1], "W": [-1, 0], "E": [1, 0]}
    rotate = {"R": -1 * pi / 180, "L": 1 * pi / 180}
    move = {"F": 1}

    pos, wp = [0, 0], [10, 1]

    for action, value in input_:
        # Update position in direction of heading
        if action in move:
            pos = [p + value * w for p, w in zip(pos, wp)]
        # Shift waypoint
        elif action in shift:
            wp = [w + value * o for w, o in zip(wp, shift[action])]
        # Rotate waypoint
        elif action in rotate:
            radians = value * rotate[action]
            dx, dy = cos(radians), sin(radians)
            wp = int(round(wp[0] * dx - wp[1] * dy)), int(
                round(wp[0] * dy + wp[1] * dx)
            )
    return abs(pos[0]) + abs(pos[1])


def main():
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 25)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input0.txt", 286)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
