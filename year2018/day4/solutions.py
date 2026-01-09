#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    output = []
    regex = re.compile(r"\[(\d{4}-\d\d-\d\d \d\d:\d\d)\] (.*)$")
    for line in input_.splitlines():
        for date, instr in regex.findall(line):
            output.append((date, instr))
    return sorted(output, key=lambda x: x[0])


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def compute_sleep_times(inp):
    regex = re.compile(r"\d+")

    sleep_times = {}
    current_guard = 0
    for i, (date, instr) in enumerate(inp):
        if "Guard" in instr:
            current_guard = int(regex.search(instr).group(0))
            if current_guard not in sleep_times:
                sleep_times[current_guard] = [0] * 60
        if "wakes" in instr:
            sleep_time = int(inp[i - 1][0][-2:])
            wakeup_time = int(date[-2:])
            for t in range(sleep_time, wakeup_time):
                sleep_times[current_guard][t] += 1
    return sleep_times


def solve_part1(input_):
    inp = transform_input(input_)

    sleep_times = compute_sleep_times(inp)
    guard = max(sleep_times, key=lambda k: sum(sleep_times[k]))
    minute, _ = max(enumerate(sleep_times[guard]), key=lambda x: x[1])
    return guard * minute


def solve_part2(input_):
    inp = transform_input(input_)

    sleep_times = compute_sleep_times(inp)

    guard = max(sleep_times, key=lambda k: max(sleep_times[k]))
    minute, _ = max(enumerate(sleep_times[guard]), key=lambda x: x[1])
    return guard * minute


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2018 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2018/day4/data/input.txt",
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
    "input1, output1", [("year2018/day4/data/test_input0.txt", 240)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2018/day4/data/test_input0.txt", 4455)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
