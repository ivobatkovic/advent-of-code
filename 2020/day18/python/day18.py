#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import re

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


class Parser:
    # Default regex for finding numbers and operators
    re_number = re.compile("(\\d+)")
    re_operator = re.compile("[^\\d]")
    # Default regex to separate, e.g., "123+456" -> "123","+", "456"
    re_operands = {0: re.compile("(-?\\d+)([\\+|\\*])(-?\\d+)")}

    def __init__(self, operator_precedence={0: ["+", "*"]}, max_op=0):
        # Update operator precedence
        for o in range(max_op + 1):
            rg = "".join("\\" + op + "|" for op in operator_precedence[o])[:-1]
            self.re_operands[o] = re.compile(f"(-?\\d+)([{rg}])(-?\\d+)")

    # Apply operation
    def operate(self, a, b, op):
        if op == "+":
            return a + b
        elif op == "*":
            return a * b
        else:
            raise ValueError("Operator not implemented")

    # Extract, e.g., "a+(b*(c+d)+f)+f"->"(b*(c+d)+f)""
    def extract_parenthesis(self, line):

        # Stop when we find a closing parenthesis
        open_id, close_id = [], []
        found_parenthesis = False
        for index, val in enumerate(line):
            if val == "(":
                open_id.append(index)
            if val == ")":
                close_id.append(index)
                if len(close_id) == len(open_id):
                    found_parenthesis = True
                    break

        if found_parenthesis:
            return line[open_id[0] : close_id[-1] + 1]
        return None

    def compute_expression(self, line):
        # Padding to handle minus sign
        line = line.replace("-", "+-")

        # Go through the operators in priority order
        for val in self.re_operands.values():
            # Keep going until all operations are completed
            while True:
                matches = val.findall(line)
                if len(matches) != 0:
                    a, op, b = matches[0]
                    output = self.operate(int(a), int(b), op)
                    line = line.replace("".join(matches[0]), str(output))
                else:
                    break
        # After all operations are done, we should have a number
        if line.isnumeric():
            return int(line)
        # Otherwise, something went wrong
        raise ValueError("Operator not defined")

    def evaluate(self, line):
        # Make sure that any spaces are removed
        line = line.replace(" ", "")

        # Find parenthes and evaulate it
        while True:
            # Get a closed parenthesis
            parenthesis = self.extract_parenthesis(line)
            if parenthesis is None:
                break
            # Compute its contents
            parse_parenthesis = self.evaluate(parenthesis[1:-1])

            # Replace the expression
            line = line.replace(parenthesis, str(parse_parenthesis))
        return self.compute_expression(line)


def transform_input(input_):
    # custom transform for the day

    return input_.splitlines()


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):
    parser = Parser()
    return sum(parser.evaluate(line) for line in input_)


def solve_part2(input_):
    parser = Parser({0: "+", 1: "*"}, 1)
    return sum(parser.evaluate(line) for line in input_)


def main():
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1",
    [
        ("../data/test_input0.txt", 71),
        ("../data/test_input1.txt", 51),
        ("../data/test_input2.txt", 26),
        ("../data/test_input3.txt", 437),
        ("../data/test_input4.txt", 12240),
        ("../data/test_input5.txt", 13632),
    ],
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("../data/test_input0.txt", 231),
        ("../data/test_input1.txt", 51),
        ("../data/test_input2.txt", 46),
        ("../data/test_input3.txt", 1445),
        ("../data/test_input4.txt", 669060),
        ("../data/test_input5.txt", 23340),
    ],
)
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
