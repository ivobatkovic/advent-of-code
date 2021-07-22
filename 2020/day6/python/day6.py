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

    group, n_groups = [[]], 0

    for inp in input_.splitlines():
        if not inp:
            n_groups += 1
            group.append([])
        else:
            # Use list of sets to keep track of individual answers
            group[n_groups].append(set(list(inp)))

    return group


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):
    """Input data is a list of [set(answer1),set(answer2),...,set(answerN)]
    for each group. Go through the input list to find size of the union"""
    return sum([len(set.union(*inp)) for inp in input_])


def solve_part2(input_):
    """For each group, find the size of the intersection"""
    return sum([len(set.intersection(*inp)) for inp in input_])


def main():

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


@pytest.mark.parametrize("input1,output1", [("../data/test_input0.txt", 11)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2,output2", [("../data/test_input0.txt", 6)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
