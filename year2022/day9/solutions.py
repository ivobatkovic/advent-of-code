#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = []
    for row in input_.splitlines():
        l, r = row.split()
        dx = 1 if l == "R" else -1 if l == "L" else 0
        dy = 1 if l == "U" else -1 if l == "D" else 0
        output.append([dx, dy, int(r)])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


class Rope:
    def __init__(self, knots):
        self.row = 0
        self.col = 0
        self.tail = Rope(knots - 1) if knots > 0 else None

    def update(self, dx, dy, mp):

        self.row += dy
        self.col += dx

        if self.tail:
            if (
                abs(self.row - self.tail.row) > 1
                or abs(self.col - self.tail.col) > 1
            ):
                if abs(self.row - self.tail.row) > 1:
                    dy = 1 if self.row > self.tail.row else -1
                    dx = min(max(self.col - self.tail.col, -1), 1)
                if abs(self.col - self.tail.col) > 1:
                    dx = 1 if self.col > self.tail.col else -1
                    dy = min(max(self.row - self.tail.row, -1), 1)
                self.tail.update(dx, dy, mp)
        else:
            mp[self.row, self.col] = 1


def solve_part1(input_):
    inp = transform_input(input_)
    mp = {(0, 0): 0}
    rope = Rope(1)
    for dx, dy, step in inp:
        for _ in range(step):
            rope.update(dx, dy, mp)
    return len(mp)


def solve_part2(input_):
    inp = transform_input(input_)
    mp = {(0, 0): 0}
    rope = Rope(9)
    for dx, dy, step in inp:
        for _ in range(step):
            rope.update(dx, dy, mp)

    return len(mp)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 9")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day9/data/input.txt",
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
    "input1, output1", [("year2022/day9/data/test_input0.txt", 13)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("year2022/day9/data/test_input0.txt", 1),
        ("year2022/day9/data/test_input1.txt", 36),
    ],
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
