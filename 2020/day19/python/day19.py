#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import re

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day
    data = input_.splitlines()

    # Dictionary to keep the rules and how they are connected
    rules = dict()
    for row, inp in enumerate(data):

        # After an empty row, we reach the messages
        if not inp:
            break

        # Separate rule number from rules
        rule_nr, *sub_rules = [i.strip() for i in inp.split(":")]
        rules[rule_nr] = list()

        # Check if the following rule is a letter
        letter = re.search("[a-z]", sub_rules[0])
        if letter:
            rules[rule_nr] = [[letter[0]]]
        # Otherwise, append the sub rules
        else:
            # Append "multiple" rule options
            for sub_rule in sub_rules[0].split("|"):
                rules[rule_nr].append([s for s in sub_rule.split()])

    # Rest if onput data consists of messages
    messages = data[row + 1 :]

    return [rules, messages]


def read_input(file_name="../data/test_input0.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def rule_check(rules, msg, rule_nums="0"):

    # If rule_nums is empty: we reached the end of the rule check
    if not rule_nums:
        return not msg  # If the message is empty, all rules passed

    # Set the first rule as the current one, and keep the remaining
    rule_num, *rule_nums = rule_nums

    # Obtain rules to check from the current rule
    rule_to_check = rules[rule_num]
    first_rule = rule_to_check[0][0]

    # Check if the first rule appearing is a letter
    if re.search("[a-z]", first_rule):
        # Check if the message starts with the rule, and the rest of the
        # message satisfies all next rules
        return msg.startswith(first_rule) and rule_check(
            rules,
            msg[len(first_rule) :],
            rule_nums,
        )
    # Otherwise, this rule connects to another one
    else:
        # Check if any group of rules in rules_to_check is satisfied. Note
        # that we append the remaining rule_nums to the number, as we need
        # to continue the search
        return any(
            rule_check(rules, msg, option + rule_nums)
            for option in rule_to_check
        )


def solve_part1(input_):
    rules, messages = input_
    return sum([1 for message in messages if rule_check(rules, message)])


def solve_part2(input_):

    rules, messages = input_
    # Modify rules
    rules["8"] = [["42"], ["42", "8"]]
    rules["11"] = [["42", "31"], ["42", "11", "31"]]
    return sum([1 for message in messages if rule_check(rules, message)])


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
        ("../data/test_input0.txt", 2),
        ("../data/test_input1.txt", 2),
        ("../data/test_input2.txt", 3),
    ],
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input2.txt", 12)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
