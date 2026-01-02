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

    twice, thrice = 0, 0

    for box_id in inp:

        twice_found = False
        thrice_found = False

        for letter in set(box_id):
            count = box_id.count(letter)

            if count == 2 and not twice_found:
                twice += 1
                twice_found = True
            if count == 3 and not thrice_found:
                thrice += 1
                thrice_found = True
    return twice * thrice


def solve_part2(input_):
    inp = transform_input(input_)

    for box_id1 in inp:
        for box_id2 in inp:
            if box_id1 == box_id2:
                continue
            mismatch = [
                i
                for i, (chr1, chr2) in enumerate(zip(box_id1, box_id2))
                if chr1 != chr2
            ]
            if len(mismatch) == 1:
                return box_id1[: mismatch[0]] + box_id1[mismatch[0] + 1 :]
    return ""


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2018 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2018/day2/data/input.txt",
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
    "input1, output1", [("year2018/day2/data/test_input0.txt", 12)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2018/day2/data/test_input1.txt", "fgij")]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
