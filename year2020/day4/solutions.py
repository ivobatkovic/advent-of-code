#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    passports = []

    passport = {}
    for line in input_.splitlines():

        if not line:
            passports.append(passport)
            passport = {}
        for entry in line.split():
            key, value = entry.split(":")
            passport[key] = value
    passports.append(passport)

    return passports


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]

    output = 0
    for passport in inp:
        output += sum([key in passport for key in fields]) == 7
    return output


def is_valid(regexes, passport):

    for key, regex in regexes.items():
        if key not in passport or not regex.match(passport[key]):
            return False
    return True


def solve_part2(input_):
    inp = transform_input(input_)

    rgx = {
        "byr": re.compile(r"^(19[2-9]\d|200[0-2])$"),
        "iyr": re.compile(r"^20(1\d|20)$"),
        "eyr": re.compile(r"^20(2\d|30)$"),
        "hgt": re.compile(r"^(1([5-8]\d|9[0-3])cm|(59|6\d|7[0-6])in)$"),
        "hcl": re.compile(r"^#[\da-f]{6}$"),
        "ecl": re.compile(r"^(amb|blu|brn|gry|grn|hzl|oth)$"),
        "pid": re.compile(r"^\d{9}$"),
    }

    output = 0
    for passport in inp:
        output += is_valid(rgx, passport)
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2020 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2020/day4/data/input.txt",
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
    "input1, output1", [("year2020/day4/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2020/day4/data/test_input1.txt", 4)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
