from os.path import dirname
from os.path import realpath
from os.path import join
import sys
import time

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))

from day5.python.intcode import Intcode


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    ic = Intcode(file_location, verbose=False)

    # Solve puzzle
    t0 = time.time()
    _, part_one = ic(1)
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    _, part_two = ic(2)
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
