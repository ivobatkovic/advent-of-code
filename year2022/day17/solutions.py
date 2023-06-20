#!/usr/bin/env python3
import argparse
import pytest
import time
from collections import defaultdict


class Rock:
    def __init__(self, shape, pos=0b0010000):
        self.shape = shape
        self.height = len(self.shape)
        self.pos = pos

    def shift(self, jet):
        if jet == "<":
            return Rock([i << 1 for i in self.shape], self.pos << 1)
        return Rock([i >> 1 for i in self.shape], self.pos >> 1)

    def is_overlapping(self, bitmasks):
        for i, bitmask in zip(self.shape, bitmasks):
            if i & bitmask:
                return True
        return False

    def is_shiftable(self, direction):
        edge = 0b0000001 if direction == ">" else 0b1000000
        for i in self.shape:
            if i & edge:
                return False
        return True


def transform_input(input_):
    rocks = [
        Rock([0b0011110][::-1]),
        Rock([0b0001000, 0b0011100, 0b0001000][::-1]),
        Rock([0b0000100, 0b0000100, 0b0011100][::-1]),
        Rock([0b0010000, 0b0010000, 0b0010000, 0b0010000][::-1]),
        Rock([0b0011000, 0b0011000][::-1]),
    ]
    jet = input_.splitlines()[0]
    return rocks, jet


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def compute_height(rocks, jets, number_of_rocks):
    bitmasks, states = defaultdict(lambda: 0), {}
    height, i_jet = 0, 0

    for i_rock in range(number_of_rocks):
        rock = rocks[i_rock % len(rocks)]
        row = height + 3
        for y in range(row, -1, -1):
            jet = jets[i_jet % len(jets)]
            i_jet += 1
            layers = [bitmasks[y + x - 1] for x in range(rock.height + 1)]
            if rock.is_shiftable(jet):
                shifted = rock.shift(jet)
                if not shifted.is_overlapping(layers[1:]):
                    rock = shifted
            if rock.is_overlapping(layers[0:-1]) or y == 0:
                for i in range(rock.height):
                    bitmasks[y + i] |= rock.shape[i]
                break
        height = max(height, y + rock.height)
        state = (i_jet % len(jets), i_rock % len(rocks), rock.pos)

        if state in states:
            prev_rock, prev_height = states[state]
            rcycle = i_rock - prev_rock
            hcycle = height - prev_height
            diff = number_of_rocks - i_rock - 1
            more, remain = divmod(diff, rcycle)
            if remain == 0:
                return hcycle * more + height
        else:
            states[state] = (i_rock, height)
    return height


def solve_part1(input_, number_of_rocks=2022):
    rocks, jets = transform_input(input_)
    return compute_height(rocks, jets, number_of_rocks)


def solve_part2(input_, number_of_rocks=int(1e12)):
    rocks, jets = transform_input(input_)
    return compute_height(rocks, jets, number_of_rocks)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 17")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day17/data/input.txt",
        nargs="?",
        help="Path to data file",
    )
    return parser.parse_args()


def main():
    parser = parse_args()
    input_ = read_input(parser.file_name)

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1:.2f}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2:.2f}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("year2022/day17/data/test_input0.txt", 3068)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day17/data/test_input0.txt", 1514285714288)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
