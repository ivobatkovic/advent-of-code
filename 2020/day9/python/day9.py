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
    return [int(inp) for inp in input_.splitlines()]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_, preamble=25):

    # Add preamble numbers to a set
    preamble_set = set(input_[:preamble])

    # Go through each number in the input list, starting after the preamble
    for i in range(preamble, len(input_)):

        # If the subtracted number is still in the preamble set: valid number
        for num in preamble_set:
            if (input_[i] - num) in preamble_set and input_[i] != 2 * num:
                break
        # If we did not break: we end up here, and the number is invalid
        else:
            return input_[i]

        # Since number was valid, update the preamble_set
        preamble_set.discard(input_[i - preamble])
        preamble_set.add(input_[i])


def solve_part2(input_, preamble=25):

    # Obtain the invalid number
    invalid_num = solve_part1(input_, preamble=preamble)

    # Increment end index until we find the invalid_num. If we go too far, we
    # we update the starting index and subtract the sum from previous entries
    start, end = 0, 0
    contiguous_sum = input_[0]
    while end < len(input_) - 1:
        if contiguous_sum < invalid_num:
            end += 1
            contiguous_sum += input_[end]
        elif contiguous_sum == invalid_num:
            contiguous_set = input_[start : end + 1]
            return min(contiguous_set) + max(contiguous_set)
        else:
            contiguous_sum -= input_[start]
            start += 1
    return "No solution"


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


@pytest.mark.parametrize(
    "input1, preamble1, output1", [("../data/test_input0.txt", 5, 127)]
)
def test1(input1, preamble1, output1):
    assert solve_part1(read_input(input1), preamble1) == output1


@pytest.mark.parametrize(
    "input2, preamble2, output2", [("../data/test_input0.txt", 5, 62)]
)
def test2(input2, preamble2, output2):
    assert solve_part2(read_input(input2), preamble2) == output2
