#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import re
import time
import pytest


def transform_input(input_):
    # custom transform for the day

    passports, n_passports = [dict()], 0

    for inp in input_.splitlines():
        if not inp:
            passports.append(dict())
            n_passports += 1
        else:
            for parts in inp.split():
                key, value = parts.split(":")
                passports[n_passports][key] = value

    return passports


def read_input(file_name="../data/input.txt"):

    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):
    # Required fields
    req = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
    # Check if all keys for each passport contain the required keys
    return sum([1 for inp in input_ if set(inp).issuperset(set(req))])


def solve_part2(input_):

    # Validation regex (nice idea from user https://github.com/hoxovic)
    rgx = {
        "byr": r"^(19[2-9]\d|200[0-2])$",
        "iyr": r"^20(1\d|20)",
        "eyr": r"^20(2\d|30)",
        "hgt": r"^(1([5-8]\d|9[0-3])cm|(59|6\d|7[0-6])in)$",
        "hcl": r"^#[\da-f]{6}",
        "ecl": r"^(amb|blu|brn|gry|grn|hzl|oth)$",
        "pid": r"^(\d{9})$",
        "cid": r"^",
    }

    def matches(inp):
        return sum(
            [1 for key, val in inp.items() if re.search(rgx[key], val)]
        ) == len(inp)

    return sum([1 for inp in input_ if solve_part1([inp]) and matches(inp)])


def main():

    input_ = read_input("../data/input.txt")
    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1,output1", [("../data/test_input0.txt", 2)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2,output2",
    [
        ("../data/test_input1.txt", 0),
        ("../data/test_input2.txt", 4),
    ],
)
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
