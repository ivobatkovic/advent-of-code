#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    crates, moving_instructions = input_.split("\n\n")

    crates = crates.splitlines()
    num_stacks = len(re.findall(r"\d+", crates[-1]))

    stacks = [[] for _ in range(num_stacks)]
    for crate in crates[::-1]:
        for i in range(num_stacks):
            if "A" <= crate[1 + i * 4] <= "Z":
                stacks[i].append(crate[1 + i * 4])

    instructions = []
    digits = re.compile(r"\d+")
    for instruction in moving_instructions.splitlines():
        instructions.append([int(x) for x in digits.findall(instruction)])

    return stacks, instructions


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve(stacks, instructions, part_two=False):
    for num, src, dst in instructions:
        stacks[dst - 1] += (
            stacks[src - 1][-num:]
            if part_two
            else stacks[src - 1][-num:][::-1]
        )
        stacks[src - 1] = stacks[src - 1][:-num]
    return "".join([x[-1] for x in stacks])


def solve_part1(input_):
    return solve(*transform_input(input_))


def solve_part2(input_):
    return solve(*transform_input(input_), part_two=True)


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
