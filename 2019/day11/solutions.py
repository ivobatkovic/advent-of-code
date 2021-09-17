from os.path import dirname
from os.path import realpath
from os.path import join
from collections import defaultdict

import sys
import numpy as np
import time


sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day5.intcode import Intcode


def get_painted_tiles(map, intcode):
    """Feeds input from the map (dict) to the intcode until it terminates.
    Returns the number of unique painted tiles."""

    px, py = 0, 0
    dir = np.pi / 2

    painted_tiles = {}

    terminated = False
    while not terminated:
        input = 0 if map[px, py] == "." else 1

        cond1, paint = intcode(input)
        cond2, turn = intcode()

        dir = dir + np.pi / 2 if turn == 0 else dir - np.pi / 2
        color = "#" if paint == 1 else "."

        if map[px, py] != color:
            painted_tiles[px, py] = 1
            map[px, py] = color

        py, px = py + int(np.cos(dir)), px - int(np.sin(dir))

        # Intcode terminated
        terminated = cond1 or cond2

    return len(painted_tiles), map


def print_map(map):
    """Given the dict map, find [xmin,xmax] and [ymin,ymax] keys to print the
    painted registration."""

    x = [key[0] for key in map.keys()]
    y = [key[1] for key in map.keys()]

    for row in range(min(x), max(x) + 1):
        msg = [
            "X" if map[row, j] == "#" else " "
            for j in range(min(y), max(y) + 1)
        ]
        print("".join(msg))


def part1(input_):
    map_part_one = defaultdict(lambda: ".")
    intcode_part_one = Intcode(input_, verbose=False, reset=False)
    part_one, _ = get_painted_tiles(map_part_one, intcode_part_one)
    return part_one


def part2(input_):
    map_part_two = defaultdict(lambda: ".")
    map_part_two[0, 0] = "#"
    intcode_part_two = Intcode(input_, verbose=False, reset=False)
    _, map_part_two = get_painted_tiles(map_part_two, intcode_part_two)
    print_map(map_part_two)


def main():

    # Open data file and read through all lines
    file_location = "data/input.txt"
    try:
        dir_path = dirname(realpath(__file__))
        with open(join(dir_path, file_location), "r") as f:
            input_ = f.read()

        t0 = time.time()
        sol_part1 = part1(input_)
        time_end = round((time.time() - t0) * 1e3)

        print(
            "Solution to part one: %s (time taken %s[ms])"
            % (sol_part1, time_end)
        )

        t0 = time.time()
        sol_part2 = part2(input_)
        time_end = round((time.time() - t0) * 1e3)
        print(
            "Solution to part two: %s (time taken %s[ms])"
            % (sol_part2, time_end)
        )
    except IOError:
        print("Cannot find file at: " + file_location)


if __name__ == "__main__":
    main()
