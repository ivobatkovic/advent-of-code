#!/usr/bin/env python3
import argparse
import pytest
import time
import queue


def transform_input(input_):
    rows = input_.splitlines()
    end = None
    for row, x in enumerate(rows):
        for col, char in enumerate(x):
            if char == "E":
                end = (row, col)
    return rows, end


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def traverse(inp, start, elevation="z", goal="S"):

    visited = {}
    q = queue.Queue()
    q.put((start, elevation, 0))

    while not q.empty():
        pos, val, dist = q.get()

        if val == goal:
            return dist

        if pos in visited:
            continue

        visited[pos] = dist
        row, col = pos
        for drow, dcol in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
            r_, c_ = row + drow, col + dcol
            if (0 <= r_ < len(inp)) and (0 <= c_ < len(inp[0])):
                next_val = "a" if inp[r_][c_] == "S" else inp[r_][c_]
                if ord(val) - ord(next_val) <= 1:
                    q.put(((r_, c_), inp[r_][c_], dist + 1))


def solve_part1(input_):
    inp, end = transform_input(input_)
    return traverse(inp, end, goal="S")


def solve_part2(input_):
    inp, end = transform_input(input_)
    return traverse(inp, end, goal="a")


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 12")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day12/data/input.txt",
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
    "input1, output1", [("year2022/day12/data/test_input0.txt", 31)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day12/data/test_input0.txt", 29)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
