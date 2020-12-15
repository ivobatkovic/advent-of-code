from os.path import dirname
from os.path import realpath
from os.path import join
import time
from maze import Maze

if __name__ == "__main__":

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    t0 = time.time()
    maze = Maze(file_location)
    part_one = maze.compute_shortest_path()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    maze_ = Maze(file_location, True)
    part_two = maze_.compute_shortest_path()
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )
