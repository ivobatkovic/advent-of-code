#!/usr/bin/env python3
import argparse
import hashlib
import pytest
import time


def transform_input(input_):
    return input_.strip()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def check_md5(key):
    md5_hash = hashlib.md5(key.encode()).digest()
    return (
        md5_hash[0] == 0
        and md5_hash[1] == 0
        and md5_hash[2] & 0b11110000 == 0,
        md5_hash.hex(),
    )


def solve_part1(input_, num=0, num_iterations=8):

    key = transform_input(input_)

    output = ""
    for _ in range(num_iterations):
        while True:
            valid, hash_hex = check_md5(key + str(num))
            num += 1

            if not valid:
                continue
            output += hash_hex[5]
            break

    return output


def solve_part2(input_, num=0, num_iterations=8):
    key = transform_input(input_)

    output = ["_"] * 8
    iterations = 0

    while True:
        valid, hash_hex = check_md5(key + str(num))
        num += 1
        if not valid:
            continue

        idx = hash_hex[5]
        if "0" <= idx < "8" and output[int(idx)] == "_":
            output[int(idx)] = hash_hex[6]

            iterations += 1
            if iterations == num_iterations:
                break

    return "".join(output)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2016 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2016/day5/data/input.txt",
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
    "input1, output1", [("year2016/day5/data/test_input0.txt", "1")]
)
def testPart1(input1, output1):
    assert (
        solve_part1(read_input(input1), num=3231000, num_iterations=1)
        == output1
    )


@pytest.mark.parametrize(
    "input2, output2", [("year2016/day5/data/test_input0.txt", "_5______")]
)
def testPart2(input2, output2):
    assert (
        solve_part2(read_input(input2), 3231000, num_iterations=1) == output2
    )
