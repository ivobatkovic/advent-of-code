#!/usr/bin/env python3
import argparse
import pytest
import time
import re


def transform_input(input_):
    tree = dict()
    name_pattern = re.compile("\\w+|\\d+")
    op_pattern = re.compile("\\+|\\-|\\/|\\*")
    for row in input_.splitlines():
        operands = re.findall(name_pattern, row)
        operator = re.findall(op_pattern, row)
        if operator:
            tree[operands[0]] = [operator[0], operands[1], operands[2]]
        else:
            tree[operands[0]] = ["", operands[1], "0"]
    return tree


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def compute(x, name):
    if name.isnumeric():
        return int(name)

    operator, val1, val2 = x[name]
    if operator == "+":
        return compute(x, val1) + compute(x, val2)
    elif operator == "-":
        return compute(x, val1) - compute(x, val2)
    elif operator == "*":
        return compute(x, val1) * compute(x, val2)
    elif operator == "/":
        return compute(x, val1) / compute(x, val2)
    return compute(x, val1)


def reverse_operation(operator, val1, val2, left_op=True):
    # Solve for x, where
    # val1 = x [+|-|/|*] val2 if left_op, otherwise
    # val1 = val2 [+|-|/|*] x
    if operator == "+":
        return val1 - val2
    elif operator == "-":
        return val1 + val2 if left_op else val2 - val1
    elif operator == "*":
        return val1 / val2
    elif operator == "/":
        return val1 * val2 if left_op else val2 / val1


def solve_part1(input_):
    return int(compute(transform_input(input_), "root"))


def check_dependency(x, name, target):
    if name == target:
        return True
    operator, val1, val2 = x[name]
    if len(operator) > 0:
        return check_dependency(x, val1, target) or check_dependency(
            x, val2, target
        )
    return False


def solve_part2(input_):
    inp = transform_input(input_)

    head = "root"
    value, tmp_value = 0, 0
    while head != "humn":
        depends_on_val1 = (
            1 if check_dependency(inp, inp[head][1], "humn") else 0
        )
        tmp_value = compute(inp, inp[head][1 + depends_on_val1])
        if head == "root":
            value = tmp_value
        else:
            value = reverse_operation(
                inp[head][0], value, tmp_value, depends_on_val1
            )
        head = inp[head][2 - depends_on_val1]
    return int(value)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 21")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day21/data/input.txt",
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
    "input1, output1", [("year2022/day21/data/test_input0.txt", 152)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day21/data/test_input0.txt", 301)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
