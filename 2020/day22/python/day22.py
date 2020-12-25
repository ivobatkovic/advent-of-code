#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day

    decks, player = [], []
    player_nr = -1
    for inp in input_.splitlines():
        if not inp:
            continue
        if "Player" in inp:
            player_nr += 1
            decks.append(player)
            player = []
        else:
            player.append(int(inp))
    decks.append(player)

    return decks[1:]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def combat(p1, p2, recursive=False):

    game_config = set()

    winner = 0
    while True:
        if recursive:
            # Player 1 wins
            if (tuple(p1), tuple(p2)) in game_config:
                return p1, 0
            # Otherwise add game configuration
            game_config.add((tuple(p1), tuple(p2)))

        # Draw card
        c1, c2 = p1[0], p2[0]

        winner = -1
        # Check if we enter a game of recursion
        if c1 <= len(p1[1:]) and c2 <= len(p2[1:]) and recursive:
            _, winner = combat(p1[1 : 1 + c1], p2[1 : 1 + c2], recursive)
        # Game rules: here, player 1 wins
        if (c1 > c2 and winner == -1) or winner == 0:
            p1, p2 = p1[1:] + [p1[0]] + [p2[0]], p2[1:]
        # Player 2 wins
        else:
            p1, p2 = p1[1:], p2[1:] + [p2[0]] + [p1[0]]

        if not p1:
            return p2, 1
        elif not p2:
            return p1, 0


def solve_part1(input_):
    # Get card decks for player 1 and player 2
    p1, p2 = input_
    # Play the combat game
    out, winner = combat(p1, p2)

    return sum(i * v for i, v in enumerate(reversed(out), 1))


def solve_part2(input_):

    # Get card decks for player 1 and player 2
    p1, p2 = input_
    # Play the combat game
    out, winner = combat(p1, p2, recursive=True)

    return sum(i * v for i, v in enumerate(reversed(out), 1))


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


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 306)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize("input2, output2", [("../data/test_input0.txt", 291)])
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
