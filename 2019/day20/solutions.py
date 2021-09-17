from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day20.donut import Donut


def part1(input_):
    donut = Donut(input_)
    return donut.shortest_path()


def part2(input_):
    donut = Donut(input_)
    return donut.shortest_path(True)


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
        ("data/test_input0.txt", 23),
        ("data/test_input1.txt", 58),
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
        ("data/test_input0.txt", 26),
        ("data/test_input2.txt", 396),
    ],
)
def test_step2(input2, steps2):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, input2), "r") as f:
        input_ = f.read()
    assert part2(input_) == steps2
