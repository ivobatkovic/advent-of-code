#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import re
from collections import defaultdict


def transform_input(input_):
    # custom transform for the day

    bag_contains = defaultdict(list)

    for sentence in input_.splitlines():
        bag, contents = sentence.split("contain")
        bag_color = re.sub("bag(.*)", "", bag).strip()
        bag_contents = [re.sub("bag.*", "", c) for c in contents.split(",")]

        for parts in bag_contents:
            # Include bag if we have something in it
            match = re.search("^\\s+(\\d+)", parts)
            if match:
                n_bags = match.group(0)
                color = parts[len(n_bags) :].strip()
                bag_contains[bag_color].append([color, int(n_bags)])

    return bag_contains


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def contains_bag(input_, color):
    if color not in input_.keys():
        return False
    return any(
        [
            True if c == "shiny gold" else contains_bag(input_, c)
            for c, _ in input_[color]
        ]
    )


def solve_part1(input_):
    # Go through each unique key and see if it leads to a shiny gold bag
    return sum([contains_bag(input_, c) for c in input_])


def bags_in_bag(bag, color, n_bags):
    if not bag[color]:
        return n_bags
    bags_in_color = 0
    for c, n in bag[color]:
        bags_in_color += n_bags * bags_in_bag(bag, c, n)
    return n_bags + bags_in_color


def solve_part2(input_):
    # Subtract 1 - don't count the "shiny gold" bag itself
    return bags_in_bag(input_, "shiny gold", 1) - 1


def main():
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1",
    [("../data/test_input0.txt", 4), ("../data/test_input2.txt", 4)],
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [("../data/test_input0.txt", 32), ("../data/test_input1.txt", 126)],
)
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
