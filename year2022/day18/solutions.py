#!/usr/bin/env python3
import argparse
import pytest
import time
from queue import Queue


def transform_input(input_):
    coords = set()
    for row in input_.splitlines():
        coords.add(tuple(map(int, row.split(","))))
    return coords


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    coords = transform_input(input_)
    neighbors = [
        (-1, 0, 0),
        (1, 0, 0),
        (0, -1, 0),
        (0, 1, 0),
        (0, 0, -1),
        (0, 0, 1),
    ]

    free_sides = 0
    for x, y, z in coords:
        for dx, dy, dz in neighbors:
            if (x + dx, y + dy, z + dz) not in coords:
                free_sides += 1
    return free_sides


def get_ranges(array, index):
    return (
        min(array, key=lambda x: x[index])[index] - 1,
        max(array, key=lambda x: x[index])[index] + 1,
    )


def solve_part2(input_):
    coords = transform_input(input_)
    neighbours = [
        (1, 0, 0),
        (-1, 0, 0),
        (0, 1, 0),
        (0, -1, 0),
        (0, 0, 1),
        (0, 0, -1),
    ]

    min_x, max_x = get_ranges(coords, 0)
    min_y, max_y = get_ranges(coords, 1)
    min_z, max_z = get_ranges(coords, 2)

    q = Queue()
    q.put((0, 0, 0))

    free_sides = 0
    visited = set((0, 0, 0))
    while not q.empty():
        x, y, z = q.get()
        for dx, dy, dz in neighbours:
            coord = (x + dx, y + dy, z + dz)
            if coord not in visited:
                if coord in coords:
                    free_sides += 1
                elif (
                    min_x <= coord[0] <= max_x
                    and min_y <= coord[1] <= max_y
                    and min_z <= coord[2] <= max_z
                ):
                    visited.add(coord)
                    q.put(coord)
    return free_sides


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 18")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day18/data/input.txt",
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
    "input1, output1", [("year2022/day18/data/test_input0.txt", 64)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day18/data/test_input0.txt", 58)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
