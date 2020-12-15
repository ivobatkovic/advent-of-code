from os.path import dirname
from os.path import realpath
from os.path import join
from asci import Asci
import time


def main(fileName):

    t0 = time.time()
    asci = Asci(fileName)
    part_one = asci.compute_intersections()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    part_two = asci.collect_dust(True)
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")
    main(file_location)
