#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    output = []
    regex = re.compile(r"(.*)-(\d+)\[(\w+)\]$")
    for line in input_.splitlines():
        output.append(regex.search(line).groups())
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def is_valid_checksum(letters, checksum):

    counts = {}

    for letter in letters.replace("-", ""):
        if letter in counts:
            counts[letter] += 1
        else:
            counts[letter] = 1

    output = "".join(sorted(counts, key=lambda k: (-counts[k], k)))[:5]

    return output == checksum


def shifted_letters_contain_northpole(letters, shift):

    offset = ord("a")
    max_val = ord("z") - offset + 1

    output = ""
    for letter in letters[:9]:
        output += chr((ord(letter) - offset + shift) % max_val + offset)

    if "northpole" in output:
        return True
    return False


def solve_part1(input_):
    inp = transform_input(input_)

    return sum(
        [
            int(sector_id)
            for letters, sector_id, checksum in inp
            if is_valid_checksum(letters, checksum)
        ]
    )


def solve_part2(input_):
    inp = transform_input(input_)

    for letters, sector_id, checksum in inp:
        if is_valid_checksum(
            letters, checksum
        ) and shifted_letters_contain_northpole(letters, int(sector_id)):
            return int(sector_id)

    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2016 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2016/day4/data/input.txt",
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
    "input1, output1", [("year2016/day4/data/test_input0.txt", 1514)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2016/day4/data/test_input1.txt", 984)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
