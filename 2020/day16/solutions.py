#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import re

sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day

    output = {"valid": dict(), "tickets": []}

    for inp in input_.splitlines():
        if " or " in inp:
            left, right = inp.split(" or ")
            name = left.split(":")[0]
            first_interval = [int(x) for x in re.findall("(\\d+)", left)]
            second_interval = [int(x) for x in re.findall("(\\d+)", right)]
            output["valid"][name] = [first_interval, second_interval]
        elif inp and "ticket" not in inp:
            output["tickets"].append([int(x) for x in inp.split(",")])
    return output


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def check(digit, valid):
    for vals in valid.values():
        for lb, ub in vals:
            if lb <= digit <= ub:
                return -1
    return digit


def part1(input_):
    input_ = transform_input(input_)
    error = 0
    for ticket in input_["tickets"][1:]:
        for nr in ticket:
            val = check(nr, input_["valid"])
            error += val if val != -1 else 0
    return error


def get_valid_tickets(input_):
    # Find any invalid ticket
    invalid_id = set()
    for id, ticket in enumerate(input_["tickets"][1:], 1):
        for nr in ticket:
            if check(nr, input_["valid"]) != -1:
                invalid_id.add(id)
                break

    # Strip away the invalid tickets
    return [x for i, x in enumerate(input_["tickets"]) if i not in invalid_id]


def get_valid_indices(name, valid, valid_tickets, indices):
    # Get the needed lower and uper bounds for the field
    [lb, ub], [lb2, ub2] = valid[name]

    # Keep track of which indices are potential candidates for a field
    valid_idx = set()

    # Go through a row for all tickets
    for index in range(len(valid_tickets[0])):

        # If we have assigned this index, skip
        if index in indices:
            continue
        #  If an index in any ticket does not match requirements, skip
        for row in range(len(valid_tickets)):
            t = valid_tickets[row][index]
            if not (lb <= t <= ub or lb2 <= t <= ub2):
                break
        # If it did match all requirements, append it to list
        else:
            valid_idx.add(index)
            # If we have found more than one match, skip this index
            if len(valid_idx) > 1:
                break

    return valid_idx


def match_field_to_index(valid_tickets, bounds):
    # Keep track of which field belongs to which index
    ids = dict()

    # Keep track of which indices we have assigned to classes
    indices = set()

    # Go through all fields once
    for field in range(len(bounds)):

        # For each field, check how many indices we potentially match with
        for name in bounds:

            if name in ids:
                continue

            valid = get_valid_indices(name, bounds, valid_tickets, indices)
            # If we have found a unique match, we assign a field to this index
            if len(valid) == 1:
                ids[name] = valid.pop()
                indices.add(ids[name])
                break
    return ids


def part2(input_):
    input_ = transform_input(input_)
    # Get only valid tickets
    valid_tickets = get_valid_tickets(input_)

    # Get the corresponding field-to-index matches
    field_index = match_field_to_index(valid_tickets, input_["valid"])

    # Compute the puzzle output
    my_ticket = valid_tickets[0]

    prod = 1
    for key in input_["valid"]:
        if "departure" in key:
            prod *= my_ticket[field_index[key]]
    return prod


def main():

    input_ = read_input()

    t0 = time.time()
    sol_part1 = part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {sol_part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    sol_part2 = part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {sol_part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1, output1", [("data/test_input0.txt", 71)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [("data/test_input1.txt", {"row": 0, "class": 1, "seat": 2})],
)
def test2(input2, output2):
    input_ = transform_input(read_input(input2))
    valid_tickets = get_valid_tickets(input_)
    field_index = match_field_to_index(valid_tickets, input_["valid"])
    assert field_index == output2
