#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import re
import math

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day

    output, instructions = [], []

    for inp in input_.splitlines():
        # Obtain the mask input
        if "mask" in inp:
            output.append(instructions)
            mask = re.search(("([\\[0|1|X]{36})"), inp).group(0)
            instructions = [mask]
        # Obtain address and value
        if "mem" in inp:
            address, value = re.findall(("(\\d+)"), inp)
            instructions.append([int(address), int(value)])
    # Add final entry
    output.append(instructions)

    # Remove first empty entry
    return output[1:]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):

    # Memory dict to place values at addresses
    memory = dict()

    # Go through each input instruction
    for instr in input_:

        # Get the mask we are using
        mask = instr[0]

        # Create masks
        on = int("".join(["1" if i == "1" else "0" for i in mask]), 2)
        enable = int("".join(["1" if i == "X" else "0" for i in mask]), 2)

        # Go through write instructions
        for adress, val in instr[1:]:
            # (enable & val) gives all bits of val under the "X" mask
            # with (enable & val) | on, we include the bits from mask "1"
            memory[adress] = (enable & val) | on

    # Go through the dict and sum all written values
    return sum([val for val in memory.values()])


def get_bits(val):
    # If value is 0 return zero bit
    if val == 0:
        return [val]
    # Otherwise get the most significant bit [10010] -> bit 5
    most_sig_bit = int(math.log(val, 2))

    # Remove the most significant bit and get the next combinations
    bits = get_bits(val ^ (2 ** most_sig_bit))

    # Go through all other bits and append the combination
    # Example: val = [1001] gives combo [1001,1000,0001,0000]
    output_bits = []
    for b in bits:
        output_bits.append(b)
        output_bits.append(val ^ b)
    return output_bits


def solve_part2(input_):

    # Memory dict to place values at addresses
    memory = dict()

    # Go through each input instruction
    for instr in input_:

        # Get the mask we are using
        mask = instr[0]

        # Create masks
        on = int("".join(["1" if i == "1" else "0" for i in mask]), 2)
        enable = int("".join(["1" if i == "X" else "0" for i in mask]), 2)
        disable = int("".join(["1" if i != "X" else "0" for i in mask]), 2)

        # Go through write instructions
        for address, val in instr[1:]:

            # Compute all bit combinations of mask X
            for bit in get_bits(enable):
                # (disable & address) gives all bits of val that are not
                # under the "X" mask. We combine it then with the active bits
                # from mask 1 and from the combinations from mask "X"
                memory[bit | (disable & address) | on] = val

    return sum([val for val in memory.values()])


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


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 165)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input1.txt", 208)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
