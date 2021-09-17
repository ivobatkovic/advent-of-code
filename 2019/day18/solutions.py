from os.path import dirname
from os.path import realpath
from os.path import join
import time
import sys
import pytest

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day18.maze import Maze


def part1(input_):
    maze = Maze(input_)
    return maze.compute_shortest_path()


def part2(input_):
    maze_ = Maze(input_, True)
    return maze_.compute_shortest_path()


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


@pytest.mark.parametrize(
    "input1,steps1",
    [
        ("data/test_input0.txt", 8),
        ("data/test_input1.txt", 86),
        ("data/test_input2.txt", 132),
        ("data/test_input3.txt", 136),
        ("data/test_input4.txt", 81),
    ],
)
def test_step1(input1, steps1):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, input1), "r") as f:
        input_ = f.read()
    assert part1(input_) == steps1


@pytest.mark.parametrize(
    "input2,steps2",
    [
        ("data/test_input5.txt", 8),
        ("data/test_input6.txt", 24),
        ("data/test_input7.txt", 32),
        ("data/test_input8.txt", 72),
    ],
)
def test_steps(input2, steps2):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, input2), "r") as f:
        input_ = f.read()
    assert part2(input_) == steps2
