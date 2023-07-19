#!/usr/bin/env python3
import argparse
import pytest
import time
from functools import cmp_to_key


def split_packet(packet):
    output = []
    depth = 0
    tmp = ""
    for x in packet[1:-1]:
        if x == "[":
            depth += 1
        elif x == "]":
            depth -= 1
        elif x == "," and depth == 0:
            output.append(tmp)
            tmp = ""
        if x != "," or (x == "," and depth != 0):
            tmp += x
    if len(tmp):
        output.append(tmp)
    return output


def transform_input(input_):
    pairs = []
    for pair in input_.split("\n\n"):
        for packet in pair.splitlines():
            pairs.append(split_packet(packet))
    return pairs


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def compare(left, right):
    for i in range(min(len(left), len(right))):
        if left[i][0] != "[" and right[i][0] != "[":
            if int(left[i]) - int(right[i]) != 0:
                return int(left[i]) - int(right[i])
        x = 0
        if left[i][0] == "[" and right[i][0] != "[":
            x = compare(
                split_packet(left[i]), split_packet("[" + right[i] + "]")
            )
        elif left[i][0] != "[" and right[i][0] == "[":
            x = compare(
                split_packet("[" + left[i] + "]"), split_packet(right[i])
            )
        else:
            x = compare(split_packet(left[i]), split_packet(right[i]))
        if x != 0:
            return x

    return len(left) - len(right)


def solve_part1(input_):
    inp = transform_input(input_)
    left, right = inp[0::2], inp[1::2]
    out = [
        i + 1 for i, (l, r) in enumerate(zip(left, right)) if compare(l, r) < 0
    ]
    return sum(out)


def solve_part2(input_):
    input_ += "[[[2]]]\n[[[6]]]"
    inp = transform_input(input_)
    inp.sort(key=cmp_to_key(compare))
    ids = [
        idx
        for idx, row in enumerate(inp, 1)
        if (len(row) > 0 and (row[0] == "[[2]]" or row[0] == "[[6]]"))
    ]
    return ids[0] * ids[1]


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 13")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day13/data/input.txt",
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
    "input1, output1", [("year2022/day13/data/test_input0.txt", 13)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day13/data/test_input0.txt", 140)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
