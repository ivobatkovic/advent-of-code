#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))

def transform_input(input_):
    return [int(x) for x in input_.splitlines()]


def read_input(file_name="2019/day1/data/input.txt"):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return sum([int(x / 3.0) - 2 for x in inp])


def compute_fuel(mass):
    fuel_needed = int(mass / 3.0) - 2
    return fuel_needed + compute_fuel(fuel_needed) if fuel_needed > 0 else 0


def solve_part2(input_):
    inp = transform_input(input_)
    return sum([compute_fuel(x) for x in inp])


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


@pytest.mark.parametrize("input1, output1", [("2019/day1/data/test_input0.txt", 33583)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("2019/day1/data/test_input0.txt", 50346)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
