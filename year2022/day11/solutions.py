#!/usr/bin/env python3
import argparse
import pytest
import time
import re


def transform_input(input_):
    return [Monkey(monkey_input) for monkey_input in input_.split("\n\n")]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


class Monkey:
    def __init__(self, inp):
        rows = inp.splitlines()
        self.items = list(map(int, re.findall("\\d+", rows[1])))
        self.processed = 0

        operand = re.search("\\d+", rows[2])
        if "+" in rows[2]:
            self.op = (
                (lambda x: x + int(operand[0]))
                if operand
                else (lambda x: x + x)
            )
        elif "-" in rows[2]:
            self.op = (
                (lambda x: x - int(operand[0]))
                if operand
                else (lambda x: x - x)
            )
        elif "*" in rows[2]:
            self.op = (
                (lambda x: x * int(operand[0]))
                if operand
                else (lambda x: x * x)
            )
        else:
            self.op = (
                (lambda x: x / int(operand[0]))
                if operand
                else (lambda x: x / x)
            )

        self.divisable = int(re.search("\\d+", rows[3])[0])
        self.true_test = int(re.search("\\d+", rows[4])[0])
        self.false_test = int(re.search("\\d+", rows[5])[0])

    def test(self, x):
        return self.true_test if x % self.divisable == 0 else self.false_test


def solve_part1(input_):
    monkeys = transform_input(input_)
    for _ in range(20):
        for monkey in monkeys:
            while monkey.items:
                item = monkey.items.pop(0)
                monkey.processed += 1
                item = monkey.op(item) // 3
                monkeys[monkey.test(item)].items.append(item)

    processed = [monkey.processed for monkey in monkeys]
    processed.sort(reverse=True)
    return processed[0] * processed[1]


def solve_part2(input_):
    monkeys = transform_input(input_)

    monkeymod = 1
    for m in monkeys:
        monkeymod *= m.divisable
    for _ in range(10000):
        for monkey in monkeys:
            while monkey.items:
                item = monkey.items.pop(0)
                monkey.processed += 1
                item = monkey.op(item) % monkeymod
                monkeys[monkey.test(item)].items.append(item)

    processed = [monkey.processed for monkey in monkeys]
    processed.sort(reverse=True)
    return processed[0] * processed[1]


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 11")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day11/data/input.txt",
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
    "input1, output1", [("year2022/day11/data/test_input0.txt", 1)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day11/data/test_input0.txt", 1)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
