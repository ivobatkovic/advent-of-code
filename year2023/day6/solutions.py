#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    durations, distances = input_.splitlines()

    regex = re.compile(r"\d+")

    return regex.findall(durations), regex.findall(distances)


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def compute(duration, distance):

    stop_duration = duration - 1
    while True:
        if stop_duration * (duration - stop_duration) > distance:
            break
        stop_duration -= 1

    start_duration = 1
    while True:
        if start_duration * (duration - start_duration) > distance:
            break
        start_duration += 1

    return stop_duration - start_duration + 1


def solve_part1(input_):
    durations, distances = transform_input(input_)

    output = 1
    for duration, distance in zip(durations, distances):
        output *= compute(int(duration), int(distance))
    return output


def solve_part2(input_):

    durations, distances = transform_input(input_)

    duration = int("".join(durations))
    distance = int("".join(distances))

    return compute(duration, distance)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2023 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2023/day6/data/input.txt",
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
    "input1, output1", [("year2023/day6/data/test_input0.txt", 288)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2023/day6/data/test_input0.txt", 71503)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
