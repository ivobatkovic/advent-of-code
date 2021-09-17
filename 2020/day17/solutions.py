#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
from itertools import product
import operator

sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day
    return [inp for inp in input_.splitlines()]


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()
    return input_


def get_potential(active, dirs, ndim):
    return {
        *[tuple(map(operator.add, pos, dir)) for pos in active for dir in dirs]
    }


def simulate(input_, ndim=3):

    # Create a set of directions and remove the origin
    directions = [[-1, 0, 1] for n in range(ndim)]
    zero_directions = [[0] for n in range(max(4 - ndim, 0))]
    dirs = set(list(product(*directions, *zero_directions)))
    dirs.remove((0,) * 4)

    # Create initial set where we have active cells
    active = {
        (h, w, 0, 0)
        for h, row in enumerate(input_)
        for w, elem in enumerate(row)
        if elem == "#"
    }

    # Apply 6 cycles
    for _ in range(6):

        # Keep track of cells that are activated
        updated = set()

        # Find potential cells that might be activated
        potential_pos = get_potential(active, dirs, ndim)

        # Go through all potential cells
        for (x, y, z, w) in potential_pos:

            count = 0
            # Search directions
            for (dx, dy, dz, dw) in dirs:
                count += 1 if (x + dx, y + dy, z + dz, w + dw) in active else 0

            if (x, y, z, w) in active and count in (2, 3):
                updated.add((x, y, z, w))
            elif (x, y, z, w) not in active and count == 3:
                updated.add((x, y, z, w))
        active = updated

    return len(active)


def part1(input_):
    return simulate(transform_input(input_))


def part2(input_):
    return simulate(transform_input(input_), 4)


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


@pytest.mark.parametrize("input1, output1", [("data/test_input0.txt", 112)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("data/test_input0.txt", 848)])
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
