#!/usr/bin/env python3
import argparse
import pytest
import time
import re
from collections import defaultdict


def compute_distance(i, j, connections):
    node = [(i, 0, set())]
    while node:
        valve, dist, visited = node.pop(0)
        if valve == j:
            return dist
        for next_valve in connections[valve]:
            if next_valve not in visited:
                node.append((next_valve, dist + 1, visited | set([valve])))


def transform_input(input_):
    connections = dict()
    flows = dict()
    for row in input_.splitlines():
        valves = re.findall("[A-Z][A-Z]", row)
        connections[valves[0]] = [valve for valve in valves[1:]]
        flow = int(re.findall("\\d+", row)[0])
        if flow != 0:
            flows[valves[0]] = flow

    valves_to_open = ["AA"] + [valve for valve in flows]
    distance_connections = dict()
    for i in valves_to_open:
        for j in valves_to_open:
            distance = compute_distance(i, j, connections)
            distance_connections[j, i] = distance
            distance_connections[i, j] = distance

    bitmask = {valve: 1 << i for i, valve in enumerate(flows)}
    return distance_connections, flows, bitmask


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    dist, flows, bitmask = transform_input(input_)

    def visit(valve, minute, pressure, open_valves, pressure_paths):
        pressure_paths[open_valves] = max(
            pressure_paths[open_valves], pressure
        )

        for next_valve, flow in flows.items():
            remaining_minutes = minute - dist[valve, next_valve] - 1
            if bitmask[next_valve] & open_valves or remaining_minutes <= 0:
                continue
            visit(
                next_valve,
                remaining_minutes,
                pressure + remaining_minutes * flow,
                open_valves | bitmask[next_valve],
                pressure_paths,
            )

    paths = defaultdict(lambda: 0)
    visit("AA", 30, 0, 0, paths)
    return max(paths.values())


def solve_part2(input_):
    dist, flows, bitmask = transform_input(input_)

    def visit(valve, minute, pressure, open_valves, pressure_paths):
        pressure_paths[open_valves] = max(
            pressure_paths[open_valves], pressure
        )

        for next_valve, flow in flows.items():
            remaining_minutes = minute - dist[valve, next_valve] - 1
            if bitmask[next_valve] & open_valves or remaining_minutes <= 0:
                continue
            visit(
                next_valve,
                remaining_minutes,
                pressure + remaining_minutes * flow,
                open_valves | bitmask[next_valve],
                pressure_paths,
            )

    paths = defaultdict(lambda: 0)
    visit("AA", 26, 0, 0, paths)
    return max(
        pressure1 + pressure2
        for open_valves1, pressure1 in paths.items()
        for open_valves2, pressure2 in paths.items()
        if not open_valves1 & open_valves2
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 16")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day16/data/input.txt",
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
    "input1, output1", [("year2022/day16/data/test_input0.txt", 1651)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day16/data/test_input0.txt", 1707)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
