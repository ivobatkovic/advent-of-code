#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day
    return [int(i) for i in input_]


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def play_game(input_, n_rounds=100, part_two=False):
    # Initialize the game
    numbers = input_
    if part_two:
        numbers += [nr for nr in range(max(numbers) + 1, 1000001)]

    # Make a directional structure,e.g., 1->2->3->...->N->1
    cups = dict()
    for index in range(len(numbers) - 1):
        cups[numbers[index]] = numbers[index + 1]
    cups[numbers[-1]] = numbers[0]

    # Start with current nr in the beginning
    current_cup = numbers[0]

    # Go through each round
    for round in range(n_rounds):

        # Get first, second, and third cup from the current_cup one
        first_cup = cups[current_cup]
        second_cup = cups[first_cup]
        third_cup = cups[second_cup]

        # Point the current cup to what the third one points to
        cups[current_cup] = cups[third_cup]

        # Get the next cup to append elements after
        next = current_cup - 1
        while True:
            # Wrap around
            if next == 0:
                next = len(numbers)
            # If the next cup has been removed, keep going
            if next in (first_cup, second_cup, third_cup):
                next -= 1
            # Otherwise, we have found the next destination cup
            else:
                break

        # Get the cup that the destination cup is pointing to
        number_after_next = cups[next]

        # Point the destination cup to the first_cup
        cups[next] = first_cup

        # Point the third cup to what the destination cup pointed to
        cups[third_cup] = number_after_next

        # Update the current cup to the one it is pointing to
        current_cup = cups[current_cup]

    return cups


def part1(input_, n_rounds=100):
    input_ = transform_input(input_)
    # Find the cup that "1" is pointing to, and keep going through the cups
    cups = play_game(input_, n_rounds=n_rounds)
    cup = cups[1]
    output = ""
    for _ in range(len(cups) - 1):
        output += str(cup)
        cup = cups[cup]
    return int(output)


def part2(input_, n_rounds=1e7):
    input_ = transform_input(input_)
    cups = play_game(input_, n_rounds=int(n_rounds), part_two=True)
    print(cups[1], cups[cups[1]])
    return cups[1] * cups[cups[1]]


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


@pytest.mark.parametrize(
    "input1, rounds1, output1",
    [
        ("data/test_input0.txt", 10, 92658374),
        ("data/test_input0.txt", 100, 67384529),
    ],
)
def test1(input1, rounds1, output1):
    assert part1(read_input(input1), rounds1) == output1


@pytest.mark.parametrize(
    "input2, output2", [("data/test_input0.txt", 149245887792)]
)
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
