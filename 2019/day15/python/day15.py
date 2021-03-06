from os.path import dirname
from os.path import realpath
from os.path import join
from droid import Droid
import time


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Part one
    t0 = time.time()
    droid = Droid(file_location)
    map, output = droid.repair_oxygen()
    part_one = output[-1]
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    part_two = droid.fill_oxygen(map, output[0], output[1])
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
