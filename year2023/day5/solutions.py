#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    data = input_.split("\n\n")
    seeds = list(map(int, re.findall(r"\d+", data[0])))

    mappings = []
    for mapping_data in data[1:]:
        mapping = {}
        for line in mapping_data.splitlines()[1:]:
            start_val, start, num = list(map(int, re.findall(r"\d+", line)))
            mapping[(start, start + num - 1)] = start_val - start
        mappings.append(mapping)

    return seeds, mappings


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def propagate_range(input_ranges, mapping):
    output_ranges = []
    for range_ in input_ranges:
        ranges_to_check = [range_]
        for (start, stop), delta in mapping.items():
            new_ranges = []
            for lo, hi in ranges_to_check:
                # No overlap with this range
                if hi < start or lo > stop:
                    new_ranges.append([lo, hi])
                    continue
                # Left part before overlap
                if lo < start:
                    new_ranges.append([lo, start - 1])

                # Overlap
                output_ranges.append(
                    [max(lo, start) + delta, min(hi, stop) + delta]
                )

                # right remainder
                if stop < hi:
                    new_ranges.append([stop + 1, hi])
            ranges_to_check = new_ranges
        output_ranges.extend(ranges_to_check)
    return output_ranges


def solve_part1(input_):
    seeds, mappings = transform_input(input_)

    output = []
    for seed in seeds:
        ranges = [[seed, seed]]
        for mapping in mappings:
            ranges = propagate_range(ranges, mapping)
        output.append(min(lo for lo, _ in ranges))
    return min(output)


def solve_part2(input_):
    seeds, mappings = transform_input(input_)

    ranges = [
        [seeds[i], seeds[i] + seeds[i + 1] - 1]
        for i in range(0, len(seeds), 2)
    ]

    for mapping in mappings:
        ranges = propagate_range(ranges, mapping)
    return min([lo for lo, _ in ranges])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2023 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2023/day5/data/input.txt",
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
    "input1, output1", [("year2023/day5/data/test_input0.txt", 35)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2023/day5/data/test_input0.txt", 46)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
