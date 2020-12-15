from os.path import dirname
from os.path import realpath
from os.path import join
from planet import Planet
import time

if __name__ == "__main__":

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    t0 = time.time()
    planet_one = Planet(file_location, recursive=False)
    part_one = planet_one.part_one()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    planet_two = Planet(file_location, recursive=True)
    part_two = planet_two.part_two()
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_one)
    )
