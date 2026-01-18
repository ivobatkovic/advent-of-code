#!/usr/bin/env python3
import argparse
import re
import pytest
import time

from collections import defaultdict


def transform_input(input_):

    rules_str, pages_str = input_.split("\n\n")
    regex = re.compile(r"\d+")

    rules = defaultdict(lambda: set())
    for rule in rules_str.splitlines():
        a, b = list(map(int, regex.findall(rule)))
        rules[a].add(b)

    pages = []
    for line in pages_str.splitlines():
        pages.append(list(map(int, regex.findall(line))))

    return rules, pages


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def check_pages(rules, pages):
    for i in range(len(pages) - 1):
        for j in range(i + 1, len(pages)):
            if pages[i] in rules[pages[j]]:
                return False
    return True


def solve_part1(input_):
    rules, list_of_pages = transform_input(input_)

    return sum(
        [
            pages[len(pages) // 2]
            for pages in list_of_pages
            if check_pages(rules, pages)
        ]
    )


def is_page_first(page, other_pages, rules):
    for other_page in other_pages:
        if page in rules[other_page]:
            return False
    return True


def fix_pages(rules, pages):

    pages_to_consider = set(pages)

    output = []
    while pages_to_consider:
        for page in pages_to_consider:
            if is_page_first(page, pages_to_consider, rules):
                output.append(page)
                pages_to_consider.remove(page)
                break
    return output


def solve_part2(input_):
    rules, list_of_pages = transform_input(input_)

    output = 0
    for pages in list_of_pages:
        if not check_pages(rules, pages):
            pages = fix_pages(rules, pages)
            output += pages[len(pages) // 2]

    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2024 day 5")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2024/day5/data/input.txt",
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
    "input1, output1", [("year2024/day5/data/test_input0.txt", 143)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2024/day5/data/test_input0.txt", 123)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
