from os.path import dirname
from os.path import realpath
from os.path import join
from pong import Pong
import time


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Part one
    t0 = time.time()
    pong = Pong(file_location)
    part_one = pong.render_map()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    pong = Pong(file_location, play=True)
    part_two = pong.play()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_two, time_part_one)
    )


if __name__ == "__main__":
    main()
