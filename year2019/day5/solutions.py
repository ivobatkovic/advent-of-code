#!/usr/bin/env python3
import argparse
import pytest
import time


class Intcode:

    def __init__(self, prog):
        self.prog = prog
        self.i = 0
        self.output = 0

    def __call__(self, input_list=[1]):
        return self.run(input_list)

    def get_opcodes(self):
        opcode = self.prog[self.i]
        op = opcode % 100
        mode1 = (opcode // 100) % 10
        mode2 = (opcode // 1000) % 10
        return op, mode1, mode2

    def operate(self, op, val1, val2):

        if op == 1:
            return val1 + val2
        elif op == 2:
            return val1 * val2
        elif op == 5:
            return val2 if val1 != 0 else self.i + 3
        elif op == 6:
            return val2 if val1 == 0 else self.i + 3
        elif op == 7:
            return val1 < val2
        elif op == 8:
            return val1 == val2

    def get_value(self, offset, mode):
        val = self.prog[offset]
        return val if mode else self.prog[val]

    def run(self, input_list):

        while True:

            op, mode1, mode2 = self.get_opcodes()

            if op == 99:
                return self.output

            if op == 1 or op == 2 or op == 7 or op == 8:
                val1 = self.get_value(self.i + 1, mode1)
                val2 = self.get_value(self.i + 2, mode2)
                dst = self.prog[self.i + 3]

                self.prog[dst] = self.operate(op, val1, val2)
                self.i += 4
            elif op == 3:
                self.prog[self.prog[self.i + 1]] = input_list.pop()
                self.i += 2
            elif op == 4:
                self.output = self.get_value(self.i + 1, mode1)
                self.i += 2
            elif op == 5 or op == 6:
                val1 = self.get_value(self.i + 1, mode1)
                val2 = self.get_value(self.i + 2, mode2)
                self.i = self.operate(op, val1, val2)


def transform_input(input_):
    return [int(x) for x in input_.split(",")]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return Intcode(inp)()


def solve_part2(input_, input_to_intcode=[5]):
    inp = transform_input(input_)
    return Intcode(inp)(input_to_intcode)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2019 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2019/day5/data/input.txt",
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


# @pytest.mark.parametrize(
# "input1, output1", [("year2019/day5/data/test_input0.txt", 1)]
# )
# def testPart1(input1, output1):
# assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("year2019/day5/data/test_input1.txt", (6, 999)),
        ("year2019/day5/data/test_input1.txt", (8, 1000)),
        ("year2019/day5/data/test_input1.txt", (10, 1001)),
    ],
)
def testPart2(input2, output2):
    input_to_intcode, expected_output = output2

    assert (
        solve_part2(read_input(input2), [input_to_intcode]) == expected_output
    )
