#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


class CRT:
    def __init__(self, inp):
        self.x = 1
        self.cycle = 0
        self.signal = 0
        self.output = ""

        for row in inp:
            if "noop" in row:
                self.update()
            else:
                for _ in range(2):
                    self.update()
                self.add(int(row[5:]))

    def update(self):
        if self.cycle % 40 == 0:
            self.output += "\n"

        if (self.cycle + 1 - 20) % 40 == 0:
            self.signal += (self.cycle + 1) * self.x

        if abs(self.cycle % 40 - self.x) <= 1:
            self.output += "#"
        else:
            self.output += "."
        self.cycle += 1

    def add(self, val):
        self.x += val


def solve_part1(input_):
    inp = transform_input(input_)
    crt = CRT(inp)
    return crt.signal


def solve_part2(input_):
    inp = transform_input(input_)
    crt = CRT(inp)
    return crt.output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 10")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day10/data/input.txt",
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
    "input1, output1", [("year2022/day10/data/test_input0.txt", 13140)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        (
            "year2022/day10/data/test_input0.txt",
            "\n"
            + "##..##..##..##..##..##..##..##..##..##..\n"
            + "###...###...###...###...###...###...###.\n"
            + "####....####....####....####....####....\n"
            + "#####.....#####.....#####.....#####.....\n"
            + "######......######......######......####\n"
            + "#######.......#######.......#######.....",
        )
    ],
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
