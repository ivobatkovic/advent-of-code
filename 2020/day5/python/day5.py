#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest


def transform_input(input_):
    # custom transform for the day

    inp = []
    for line in input_.splitlines():
        row, col = [0, 127], [0, 7]
        for seat in line:
            if seat == "B":
                row[0] = (row[0] + 1 + row[1]) // 2
            elif seat == "F":
                row[1] = (row[0] + row[1]) // 2
            elif seat == "R":
                col[0] = (col[0] + 1 + col[1]) // 2
            elif seat == "L":
                col[1] = (col[0] + col[1]) // 2
        inp.append([min(row), min(col)])

    return inp


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):
    # Compute the seat ids from the input and return the max element
    return max([row * 8 + col for row, col in input_])


def solve_part2(input_):

    # Go through input and sort it
    sorted_ids = sorted([row * 8 + col for row, col in input_])

    # See if next seat id is not offseted by 1, then we found our empty seat
    for i, v in enumerate(sorted_ids[:-1]):
        if abs(v - sorted_ids[i + 1]) > 1:
            return v + 1


def main():

    input_ = read_input("../data/test_input0.txt")
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1,output1",
    [
        ("../data/test_input0.txt", 357),
        ("../data/test_input1.txt", 567),
        ("../data/test_input2.txt", 119),
        ("../data/test_input3.txt", 820),
    ],
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1
