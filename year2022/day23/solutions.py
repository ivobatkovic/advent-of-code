#!/usr/bin/env python3
import argparse
import pytest
import time
from collections import defaultdict


def transform_input(input_):

    elves = set()
    for y, row in enumerate(input_.splitlines()):
        for x, char in enumerate(row):
            if char == "#":
                elves.add((y, x))
    return elves


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def propose_move(elves, elf):
    y, x = elf
    return (
        ((y - 1, x - 1) in elves)
        or ((y - 1, x) in elves)
        or ((y - 1, x + 1) in elves)
        or ((y, x - 1) in elves)
        or ((y, x + 1) in elves)
        or ((y + 1, x - 1) in elves)
        or ((y + 1, x) in elves)
        or ((y + 1, x + 1) in elves)
    )


def get_proposal(elf, elves, direction):
    y, x = elf
    for i in range(4):
        if (direction + i) % 4 == 0:
            if (
                ((y - 1, x - 1) not in elves)
                and ((y - 1, x) not in elves)
                and ((y - 1, x + 1) not in elves)
            ):
                return (y - 1, x)
        elif (direction + i) % 4 == 1:
            if (
                ((y + 1, x - 1) not in elves)
                and ((y + 1, x) not in elves)
                and ((y + 1, x + 1) not in elves)
            ):
                return (y + 1, x)
        elif (direction + i) % 4 == 2:
            if (
                ((y - 1, x - 1) not in elves)
                and ((y, x - 1) not in elves)
                and ((y + 1, x - 1) not in elves)
            ):
                return (y, x - 1)
        else:
            if (
                ((y - 1, x + 1) not in elves)
                and ((y, x + 1) not in elves)
                and ((y + 1, x + 1) not in elves)
            ):
                return (y, x + 1)
    return (y, x)


def move_elves(elves, part1=True):
    direction, rounds = 0, 0

    while True:
        rounds += 1

        # Generate movement proposals
        proposed_moves = defaultdict(lambda: 0)
        for elf in elves:
            if propose_move(elves, elf):
                (yp, xp) = get_proposal(elf, elves, direction)
                proposed_moves[(yp, xp)] += 1

        if len(proposed_moves) == 0:
            return rounds

        # Check movement proposals and update
        elves_ = set()
        for elf in elves:
            if propose_move(elves, elf):
                (yp, xp) = get_proposal(elf, elves, direction)

                if proposed_moves[(yp, xp)] == 1:
                    elves_.add((yp, xp))
                else:
                    elves_.add(elf)
            else:
                elves_.add(elf)

        direction += 1
        elves = elves_

        if part1 and rounds == 10:
            break
    keys = [key for key in elves]

    min_x = min([x for (_, x) in keys])
    max_x = max([x for (_, x) in keys])
    min_y = min([y for (y, _) in keys])
    max_y = max([y for (y, _) in keys])
    return (max_x + 1 - min_x) * (max_y + 1 - min_y) - len(elves)


def solve_part1(input_):
    elves = transform_input(input_)
    return move_elves(elves)


def solve_part2(input_):
    elves = transform_input(input_)
    return move_elves(elves, False)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 23")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day23/data/input.txt",
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
    "input1, output1", [("year2022/day23/data/test_input0.txt", 110)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day23/data/test_input0.txt", 20)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
