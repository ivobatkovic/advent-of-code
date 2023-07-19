#!/usr/bin/env python3
import argparse
import pytest
import time
import re
from collections import defaultdict


def transform_input(input_):
    stacks = defaultdict(list)
    header = []
    for row in input_.splitlines():
        if not row:
            break
        header.append(row)
    header.reverse()

    for row in header:
        for idx, character in enumerate(row[1:-1:4], 1):
            if character == " ":
                continue
            stacks[idx].append(character)

    instructions = []
    for row in input_.splitlines()[len(header) + 1 :]:
        instructions.append(list(map(int, re.findall("\\d+", row))))

    return stacks, instructions


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def move_stacks(stacks, n_items, dst, src, reverse=True):
    items = stacks[dst][-n_items:]
    if reverse:
        items.reverse()
    stacks[dst] = stacks[dst][:-n_items]
    stacks[src] = stacks[src] + items


def solve_part1(input_):
    stacks, instructions = transform_input(input_)

    for n_items, dst, src in instructions:
        move_stacks(stacks, n_items, dst, src)
    return "".join(stacks[i][-1] for i in range(1, len(stacks) + 1))


def solve_part2(input_):
    stacks, instructions = transform_input(input_)

    for n_items, dst, src in instructions:
        move_stacks(stacks, n_items, dst, src, reverse=False)
    return "".join(stacks[i][-1] for i in range(1, len(stacks) + 1))


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day5/data/input.txt",
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
    "input1, output1", [("year2022/day5/data/test_input0.txt", "CMZ")]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day5/data/test_input0.txt", "MCD")]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
