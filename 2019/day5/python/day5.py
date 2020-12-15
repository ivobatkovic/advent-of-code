from intcode import Intcode
from os.path import dirname
from os.path import realpath
from os.path import join
import time


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    intcode = Intcode(file_location, verbose=False, reset=True)

    t0 = time.time()
    _, part_one = intcode(1)
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    _, part_two = intcode(5)
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
