#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


class Console:
    def __init__(self, file_name="../data/input.txt"):
        self.program = self.read_input(file_name)
        self.n_instructions = len(self.program)
        self.reset()

    def reset(self):
        self.accumulator, self.offset = 0, 0
        self.processed_instructions = set()

    def transform_input(self, input_):
        # custom transform for the day

        def process(x):
            return [x[0], int(x[1])]

        return [process(inp.split()) for inp in input_.splitlines()]

    def read_input(self, file_name):
        with open(file_name, "r") as f:
            input_ = self.transform_input(f.read())
        return input_

    def __call__(self):

        while True and self.offset < self.n_instructions:
            op, val = self.program[self.offset]
            if self.offset in self.processed_instructions:
                output = self.accumulator
                self.reset()
                return output, False
            self.processed_instructions.add(self.offset)

            if op == "acc":
                self.accumulator += val
            elif op == "jmp":
                self.offset += val - 1
            self.offset += 1

        # Reset
        output = self.accumulator
        self.reset()
        return output, True


def read_input(file_name="../data/input.txt"):
    return join(dirname(realpath(__file__)), file_name)


def solve_part1(input_):
    return Console(file_name=input_)()[0]


def solve_part2(input_):

    console = Console(file_name=input_)
    for line in range(len(console.program)):

        # Modify instruction
        op = console.program[line][0]
        if op == "nop":
            console.program[line][0] = "jmp"
        elif op == "jmp":
            console.program[line][0] = "nop"

        # Evaluate instruction - if <cond> is true, we terminated naturally
        val, cond = console()
        if cond:
            return val

        # Reset input
        console.program[line][0] = op


def main():
    input_ = read_input()
    print(input_)
    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 5)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input0.txt", 8)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
