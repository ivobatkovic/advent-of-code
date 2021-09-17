from os.path import dirname
from os.path import realpath
from os.path import join
import time
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day24.planet import Planet


def part1(input_):
    planet_one = Planet(input_, recursive=False)
    return planet_one.part_one()


def part2(input_):
    planet_two = Planet(input_, recursive=True)
    return planet_two.part_two()


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
