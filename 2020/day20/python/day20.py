#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import re

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))

from jiggsaw import Jiggsaw


def transform_input(input_):
    # custom transform for the day
    image = dict()

    # Go through each line
    for inp in input_.splitlines():
        # Skip empty line
        if not inp:
            continue
        # Check for tile number
        tile = re.search("(\\d+)", inp)
        if tile:
            tile_nr = tile[0]
            image[tile_nr] = []
        # If no tile number, append the row to the current tile
        else:
            image[tile_nr].append(inp)

    return image


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):
    # Feed the Jiggsaw class all image pieces
    jigsaw = Jiggsaw(input_)
    jigsaw.solve()

    prod = 1
    for pos in jigsaw.get_corners():
        prod *= int(pos)
    return prod


def solve_part2(data):

    jiggsaw = Jiggsaw(data)
    jiggsaw.solve()

    monster = [
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   ",
    ]

    return jiggsaw.get_rough_waters(monster)


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
    "input1, output1", [("../data/test_input0.txt", 20899048083289)]
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input0.txt", 273)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
