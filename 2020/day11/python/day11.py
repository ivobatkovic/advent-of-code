#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys
import copy

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day
    rows = input_.splitlines()

    # Pad the input data so that we can traverse the grid easier later
    inp = [" " * (len(rows[0]) + 2)]
    for row in rows:
        inp.append(" " + row + " ")
    inp.append(" " * (len(rows[0]) + 2))
    return inp


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def get_seat_positions(input_):
    # Return positions <row,col> for all empty seats
    return [
        [row, col]
        for row, v in enumerate(input_)
        for col, val in enumerate(v)
        if val == "L"
    ]


def get_neighbor_directions():
    # Return: top left, top, top right, left, right, bot left, bot, bot right
    return [
        (x, y)
        for x in range(-1, 2)
        for y in range(-1, 2)
        if not (x == 0 and y == 0)
    ]


def update_seats(input_, seat_positions, neighbors, adjacent_seats=4):
    # Copy seat arrangements
    seats = copy.deepcopy(input_)

    while True:
        # Need to keep track of the old configuration while updating the new
        old_seats = copy.copy(seats)

        # Keep track if we performed a change
        changed = False

        # Go through each position and check for the rules
        for row, col in seat_positions:

            # Check how many neighbors are occupied
            occupied = 0
            for row_, col_ in neighbors[row, col]:
                if old_seats[row_][col_] == "#":
                    occupied += 1

            # Update rules
            if old_seats[row][col] == "L" and occupied == 0:
                seats[row] = seats[row][:col] + "#" + seats[row][col + 1 :]
                changed = True
            elif old_seats[row][col] == "#" and occupied >= adjacent_seats:
                seats[row] = seats[row][:col] + "L" + seats[row][col + 1 :]
                changed = True
        # We are done when no more seats are changing
        if not changed:
            break

    # Count the number of # in the final configuration
    return "".join(seats).count("#")


def get_neighbors_part1(input_, seat_position):
    adjacent = get_neighbor_directions()
    neighbors = dict()
    # Go through each position and see if we have an empty seat next to us
    for row, col in seat_position:
        neighboring = []
        for dx, dy in adjacent:
            if input_[row + dx][col + dy] == "L":
                neighboring.append([row + dx, col + dy])
        neighbors[row, col] = neighboring
    return neighbors


def solve_part1(input_):

    seat_positions = get_seat_positions(input_)
    neighbors = get_neighbors_part1(input_, seat_positions)
    return update_seats(input_, seat_positions, neighbors, 4)


def get_neighbors_part2(input_, seat_position):
    adjacent = get_neighbor_directions()
    neighbors = dict()

    # Go through each position and see if we can find an empty seat
    for row, col in seat_position:
        neighboring = []
        # Traverse in direction dx,dy until we reach a seat or the end
        for dx, dy in adjacent:
            row_ = row + dx
            col_ = col + dy
            while True:
                if input_[row_][col_] != ".":
                    break
                row_ += dx
                col_ += dy
            # Check if we reached a seat (remember we pad with " ")
            if input_[row_][col_] == "L":
                neighboring.append([row_, col_])
        neighbors[row, col] = neighboring
    return neighbors


def solve_part2(input_):
    seat_positions = get_seat_positions(input_)
    neighbors = get_neighbors_part2(input_, seat_positions)
    return update_seats(input_, seat_positions, neighbors, 5)


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


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 37)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input0.txt", 26)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
