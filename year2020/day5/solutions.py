#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for line in inp:
        rows, cols = [0, 127], [0, 8]
        for char in line:
            if char == "F":
                rows[1] = sum(rows) // 2
            elif char == "B":
                rows[0] = (sum(rows) + 1) // 2
            elif char == "L":
                cols[1] = sum(cols) // 2
            elif char == "R":
                cols[0] = (sum(cols) + 1) // 2

        output = max(output, min(rows) * 8 + min(cols))
    return output


def solve_part2(input_):
    inp = transform_input(input_)

    ids = set()
    for line in inp:
        rows, cols = [0, 127], [0, 8]
        for char in line:
            if char == "F":
                rows[1] = sum(rows) // 2
            elif char == "B":
                rows[0] = (sum(rows) + 1) // 2
            elif char == "L":
                cols[1] = sum(cols) // 2
            elif char == "R":
                cols[0] = (sum(cols) + 1) // 2

        ids.add(min(rows) * 8 + min(cols))

    for x in ids:
        if (x + 1) not in ids and (x + 2) in ids:
            return x + 1

    return "Implement part two"


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2020 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2020/day5/data/input.txt",
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
    "input1, output1", [("year2020/day5/data/test_input0.txt", 357)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2020/day5/data/input.txt", 615)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
