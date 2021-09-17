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

    output = []
    for inp in input_.splitlines():
        count, letter, pw = inp.replace(":", "").split()
        low, high = count.split("-")
        output.append([int(low), int(high), letter, pw])
    return output


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def part1(input_):
    input_ = transform_input(input_)
    n_pws = 0
    for low, high, letter, pw in input_:
        n_pws += 1 if low <= pw.count(letter) <= high else 0
    return n_pws


def part2(input_):
    input_ = transform_input(input_)
    n_pws = 0
    for low, high, letter, pw in input_:
        n_pws += 1 if (pw[low - 1] == letter) ^ (pw[high - 1] == letter) else 0
    return n_pws


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


@pytest.mark.parametrize("input1,output1", [("data/test_input0.txt", 2)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2,output2", [("data/test_input0.txt", 1)])
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
