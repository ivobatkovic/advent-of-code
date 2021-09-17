#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day
    return input_.splitlines()


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def part1(input_):
    input_ = transform_input(input_)
    h, w = len(input_), len(input_[0])

    dy, dx = 1, 3
    s = 0
    for y in range(h - 1):
        s += 1 if input_[y + dy][(y + dy) * dx % w] == "#" else 0
    return s


def part2(input_):
    input_ = transform_input(input_)
    h, w = len(input_), len(input_[0])

    x_diff = [1, 3, 5, 7] + [0.5]
    y_diff = [1] * 4 + [2]

    prodTrees = 1
    for dx, dy in zip(x_diff, y_diff):
        nTrees = 0
        for y in range(0, h - 1, dy):
            nTrees += 1 if input_[y + dy][int((y + dy) * dx) % w] == "#" else 0
        prodTrees *= nTrees

    return prodTrees


def main():

    input_ = read_input()

    t0 = time.time()
    sol_part1 = part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {sol_part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    sol_part2 = part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {sol_part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1,output1", [("data/test_input0.txt", 7)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2,output2", [("data/test_input0.txt", 336)])
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
