#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return [(idx, int(val)) for (idx, val) in enumerate(input_.splitlines())]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def mix(sequence, nr_times=1, key=1):
    n = len(sequence)

    for _ in range(nr_times):
        for i in range(n):
            for j in range(n):
                if sequence[j][0] == i:
                    break

            val = sequence[j][1]
            sequence.pop(j)

            j = (j + val * key) % (n - 1)
            sequence.insert(j, (i, val))

    for i in range(n):
        if sequence[i][1] == 0:
            break
    values = [1000, 2000, 3000]
    return sum([sequence[(i + v) % n][1] * key for v in values])


def solve_part1(input_):
    inp = transform_input(input_)
    return mix(inp)


def solve_part2(input_):
    inp = transform_input(input_)
    return mix(inp, 10, 811589153)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 20")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day20/data/input.txt",
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
    "input1, output1", [("year2022/day20/data/test_input0.txt", 3)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day20/data/test_input0.txt", 1623178306)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
