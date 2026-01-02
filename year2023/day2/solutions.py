#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    regex = re.compile("\\d+ \\w+")
    games = []
    for line in input_.splitlines():

        subsets = line.split(";")
        game = []
        for subset in subsets:
            rgb = [0, 0, 0]
            for match in regex.findall(subset):
                val, color = match.split()
                if color == "red":
                    rgb[0] += int(val)
                elif color == "green":
                    rgb[1] += int(val)
                elif color == "blue":
                    rgb[2] += int(val)
            game.append(rgb)
        games.append(game)
    return games


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for i, game in enumerate(inp, 1):
        possible = True
        for r, g, b in game:
            if r > 12 or g > 13 or b > 14:
                possible = False
                break
        if possible:
            output += i
    return output


def solve_part2(input_):
    inp = transform_input(input_)
    output = 0
    for i, game in enumerate(inp, 1):

        R, G, B = 0, 0, 0
        for r, g, b in game:
            R, G, B = max(R, r), max(G, g), max(B, b)
        output += R * G * B
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2023 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2023/day2/data/input.txt",
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
    "input1, output1", [("year2023/day2/data/test_input0.txt", 8)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2023/day2/data/test_input0.txt", 2286)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
