#!/usr/bin/env python3
import argparse
import copy
import pytest
import time


class Intcode:

    def __init__(self, prog):
        self.prog = prog
        self.i = 0
        self.run()

    def run(self):

        while True:
            op = self.prog[self.i]
            if op == 99:
                return

            a, b, dst = self.prog[self.i + 1 : self.i + 4]

            if op == 1:
                self.prog[dst] = self.prog[a] + self.prog[b]
            elif op == 2:
                self.prog[dst] = self.prog[a] * self.prog[b]

            self.i += 4


def transform_input(input_):
    return [int(x) for x in input_.split(",")]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_, modify=True):

    inp = transform_input(input_)
    if modify:
        inp[1] = 12
        inp[2] = 2

    ic = Intcode(inp)
    return ic.prog[0]


def solve_part2(input_):
    inp = transform_input(input_)

    for noun in range(99):
        for verb in range(99):
            inp[1], inp[2] = noun, verb
            if Intcode(copy.copy(inp)).prog[0] == 19690720:
                return 100 * noun + verb
    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2019 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2019/day2/data/input.txt",
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
    "input1, output1", [("year2019/day2/data/test_input0.txt", 3500)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1), False) == output1
