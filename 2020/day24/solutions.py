#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import re

sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day

    return [
        re.findall(r"(ne|se|nw|sw|e|w)", inp) for inp in input_.splitlines()
    ]


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def traverse(input_):
    # Directions to move in the hex grid
    dir = {
        "e": [0, 1],
        "w": [0, -1],
        "se": [1, 0.5],
        "sw": [1, -0.5],
        "ne": [-1, 0.5],
        "nw": [-1, -0.5],
    }

    # Keep track of flipped (black) positions
    tiles = set()
    for instructions in input_:
        # Follow instructions from (0,0)
        pos = tuple([0, 0])
        for instruction in instructions:
            pos = tuple([sum(x) for x in zip(pos, dir[instruction])])
        # If the tile is black -> turn it white
        if pos in tiles:
            tiles.remove(pos)
        # If the tile is white -> turn it black
        else:
            tiles.add(pos)
    return tiles


def part1(input_):
    return len(traverse(transform_input(input_)))


def get_active(tile, neighbors):
    # Consider all black tiles and their neighbors
    active_tile = set()
    for pos in tile:
        active_tile.add(pos)
        [
            active_tile.add(tuple([pos[0] + dy, pos[1] + dx]))
            for dy, dx in neighbors
        ]

    return active_tile


def part2(input_):
    tile = traverse(transform_input(input_))
    neighbors = [[0, 1], [0, -1], [1, 0.5], [1, -0.5], [-1, 0.5], [-1, -0.5]]

    # Update the tiles n times
    for _ in range(100):
        # Get all potential tiles that can flip
        potential_tiles = get_active(tile, neighbors)

        # Keep track of black tiles
        update = set()

        for pos in potential_tiles:
            # Check how many black neighbors the tile has
            count = 0
            for dy, dx in neighbors:
                count += 1 if tuple([pos[0] + dy, pos[1] + dx]) in tile else 0
            # Decide to flip or not
            if pos not in tile and count == 2:
                update.add(pos)
            elif pos in tile and count != 0 and count <= 2:
                update.add(pos)
        tile = update

    return len(tile)


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


@pytest.mark.parametrize("input1, output1", [("data/test_input0.txt", 10)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("data/test_input0.txt", 2208)])
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
