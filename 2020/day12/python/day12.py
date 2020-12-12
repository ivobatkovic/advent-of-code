#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

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

    shift = {"N": 1j, "S": -1j, "W": -1, "E": 1}
    rotate = {"L": 1j, "R": -1j}

    pos, heading = 0, 1
    for action, value in input_:

        # Shift action north/south/west/east
        if action in shift:
            pos += shift[action] * value
        # Change direction left or right
        elif action in rotate:
            heading *= rotate[action] ** (value // 90)
        # Update position in direction of heading
        else:
            pos += heading * value
    return int(abs(pos.real) + abs(pos.imag))


def solve_part2(input_):

    shift = {"N": 1j, "S": -1j, "W": -1, "E": 1}
    rotate = {"L": 1j, "R": -1j}

    pos, wp = 0, 10 + 1j

    for action, value in input_:
        # Shift action north/south/west/east
        if action in shift:
            wp += shift[action] * value
        # Rotate waypoint
        elif action in rotate:
            wp *= rotate[action] ** (value // 90)
        # Update position in direction of waypoint
        else:
            pos += wp * value
    return int(abs(pos.real) + abs(pos.imag))


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
