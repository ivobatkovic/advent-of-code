#!/usr/bin/env python3
import argparse
import pytest
import time

from collections import defaultdict, deque


def transform_input(input_):

    orbits = defaultdict(lambda: [])

    for connection in input_.splitlines():
        src, dst = connection.split(")")
        orbits[src].append(dst)
        orbits[dst].append(src)
    return orbits


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    orbits = transform_input(input_)

    q = deque([("COM", 0)])
    visited = set()

    output = 0
    while q:
        src, depth = q.popleft()

        if src in visited:
            continue
        visited.add(src)

        output += depth

        for dst in orbits[src]:
            q.append((dst, depth + 1))
    return output


def solve_part2(input_):
    orbits = transform_input(input_)

    q = deque([("YOU", 0)])
    visited = {"YOU"}

    while q:
        src, depth = q.popleft()

        if src == "SAN":
            return depth - 2

        for dst in orbits[src]:
            if dst not in visited:
                visited.add(dst)
                q.append((dst, depth + 1))
    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2019 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2019/day6/data/input.txt",
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
    "input1, output1", [("year2019/day6/data/test_input0.txt", 42)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2019/day6/data/test_input1.txt", 4)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
