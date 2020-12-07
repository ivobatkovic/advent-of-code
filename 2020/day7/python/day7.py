#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
from collections import defaultdict
from queue import Queue


def transform_input(input_):
    # custom transform for the day

    # bag_contained_by[key] = list of bag_color
    bag_contained_by = defaultdict(list)
    # bag_contains[key] = list of [bag_color, n_bags]
    bag_contains = defaultdict(list)

    for inp in input_.splitlines():
        sentence = inp.split()

        # Figure out bag color
        bag = sentence[0] + " " + sentence[1]

        # Append the contained bags
        for i in range(4, len(sentence), 4):
            num_bags = sentence[i]
            bag_color = sentence[i + 1] + " " + sentence[i + 2]
            if num_bags != "no":
                bag_contains[bag].append([bag_color, int(num_bags)])
                bag_contained_by[bag_color].append(bag)

    return [bag_contained_by, bag_contains]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):

    bag_contained_by = input_[0]
    # Number of colors that contain "shiny gold"
    n_colors = set()

    # Go through the input_ dictionary
    q = Queue()
    q.put("shiny gold")
    while not q.empty():
        colors = q.get()
        if not bag_contained_by[colors]:
            continue
        for color in bag_contained_by[colors]:
            n_colors.add(color)
            q.put(color)
    return len(n_colors)


def bags_in_bag(bag, color, n_bags):
    if not bag[color]:
        return n_bags
    bags_in_color = 0
    for c, n in bag[color]:
        bags_in_color += n_bags * bags_in_bag(bag, c, n)
    return n_bags + bags_in_color


def solve_part2(input_):
    bag, num_bags = input_[1], 0

    return bags_in_bag(bag, "shiny gold", 1) - 1
    for colors, n_bags in bag["shiny gold"]:
        num_bags += bags_in_bag(bag, colors, n_bags)
    return num_bags


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


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 4)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [("../data/test_input0.txt", 32), ("../data/test_input1.txt", 126)],
)
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
