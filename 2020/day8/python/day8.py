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

    def process(x):
        return [x[0], int(x[1])]

    return [process(inp.split()) for inp in input_.splitlines()]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):
    offset, glob_value = 0, 0
    d = dict()

    input_size = len(input_)
    while True and offset < input_size:

        op, val = input_[offset]
        opval_string = op + str(val) + "line" + str(offset)
        if opval_string in d:
            return glob_value, False
        d[opval_string] = glob_value

        if op == "acc":
            glob_value += val
        elif op == "jmp":
            offset += val - 1
        offset += 1

    return glob_value, True


def solve_part2(input_):

    cond = False
    for i in range(len(input_)):
        # Modify instruction
        op = input_[i][0]
        if op == "nop":
            input_[i][0] = "jmp"
        elif op == "jmp":
            input_[i][0] = "nop"

        # Evaluate instruction - if <cond> is true, we terminated naturally
        val, cond = solve_part1(input_)
        if cond:
            return val

        # Reset input
        input_[i][0] = op


def main():
    input_ = read_input()

    t0 = time.time()
    part1, _ = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("../data/test_input0.txt", (5, False))]
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input1.txt", 8)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
