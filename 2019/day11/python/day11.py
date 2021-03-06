from os.path import dirname
from os.path import realpath
from os.path import join
from collections import defaultdict

import sys
import numpy as np
import time

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))

from day5.python.intcode import Intcode


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


def main():
    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Part one
    t0 = time.time()
    map_part_one = defaultdict(lambda: ".")
    intcode_part_one = Intcode(file_location, verbose=False, reset=False)
    part_one, _ = get_painted_tiles(map_part_one, intcode_part_one)
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    # Part two
    t0 = time.time()
    map_part_two = defaultdict(lambda: ".")
    map_part_two[0, 0] = "#"
    intcode_part_two = Intcode(file_location, verbose=False, reset=False)
    _, map_part_two = get_painted_tiles(map_part_two, intcode_part_two)
    print("Solution to part two:")
    print_map(map_part_two)
    time_part_two = round((time.time() - t0) * 1e3)
    print("(time taken %s[ms])" % time_part_two)


if __name__ == "__main__":
    main()
