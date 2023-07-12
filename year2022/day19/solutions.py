#!/usr/bin/env python3
import argparse
import pytest
import time
import re
from collections import deque


def transform_input(input_):
    pattern = re.compile("\\d+")
    blueprints = []
    for row in input_.splitlines():
        cost = list(map(int, re.findall(pattern, row)))
        blueprints.append(cost[1:])
    return blueprints


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def limitStates(
    state,
    max_ore_cost,
    clay_cost_obs,
    obs_cost_geo,
):
    o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t = state

    # Can only make one robot per time instance. Having more
    # ore/clay/obsidian robots than what it costs to make an
    # upgrade does not help.
    if ore_r >= max_ore_cost:
        ore_r = max_ore_cost
    if clay_r >= clay_cost_obs:
        clay_r = clay_cost_obs
    if obs_r >= obs_cost_geo:
        obs_r = obs_cost_geo
    # Same with number of ores - we can ignore ores that will never be used
    if o >= t * max_ore_cost - ore_r * (t - 1):
        o = t * max_ore_cost - ore_r * (t - 1)
    if c >= t * clay_cost_obs - clay_r * (t - 1):
        c = t * clay_cost_obs - clay_r * (t - 1)
    if ob >= t * obs_cost_geo - obs_r * (t - 1):
        ob = t * obs_cost_geo - obs_r * (t - 1)
    return o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t


def solve(cost, minutes):

    (
        ore_cost,
        clay_cost,
        ore_cost_obs,
        clay_cost_obs,
        ore_cost_geo,
        obs_cost_geo,
    ) = cost

    max_geodes = 0
    #      ores                  |
    # ore, clay, obsidian, geode | ore, clay, obsidian, geode | time
    state = (0, 0, 0, 0, 1, 0, 0, 0, minutes)
    q = deque([state])
    visited = set()
    max_ore_cost = max([ore_cost, clay_cost, ore_cost_obs, ore_cost_geo])

    while q:

        state = q.popleft()
        max_geodes = max(max_geodes, state[3])

        if state[-1] == 0:
            continue

        # Limited state space - helps with caching
        state = limitStates(state, max_ore_cost, clay_cost_obs, obs_cost_geo)

        if state in visited:
            continue
        visited.add(state)

        o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t = state
        # Step without buying
        q.append(
            (
                o + ore_r,
                c + clay_r,
                ob + obs_r,
                g + geo_r,
                ore_r,
                clay_r,
                obs_r,
                geo_r,
                t - 1,
            )
        )

        if o >= ore_cost:
            q.append(
                (
                    o - ore_cost + ore_r,
                    c + clay_r,
                    ob + obs_r,
                    g + geo_r,
                    ore_r + 1,
                    clay_r,
                    obs_r,
                    geo_r,
                    t - 1,
                )
            )
        if o >= clay_cost:
            q.append(
                (
                    o - clay_cost + ore_r,
                    c + clay_r,
                    ob + obs_r,
                    g + geo_r,
                    ore_r,
                    clay_r + 1,
                    obs_r,
                    geo_r,
                    t - 1,
                )
            )

        if o >= ore_cost_obs and c >= clay_cost_obs:
            q.append(
                (
                    o - ore_cost_obs + ore_r,
                    c - clay_cost_obs + clay_r,
                    ob + obs_r,
                    g + geo_r,
                    ore_r,
                    clay_r,
                    obs_r + 1,
                    geo_r,
                    t - 1,
                )
            )
        if o >= ore_cost_geo and ob >= obs_cost_geo:
            q.append(
                (
                    o - ore_cost_geo + ore_r,
                    c + clay_r,
                    ob - obs_cost_geo + obs_r,
                    g + geo_r,
                    ore_r,
                    clay_r,
                    obs_r,
                    geo_r + 1,
                    t - 1,
                )
            )
    return max_geodes


def solve_part1(input_, minutes=24):
    blueprints = transform_input(input_)
    output = 0
    for idx, bp in enumerate(blueprints, 1):
        output += idx * solve(bp, minutes)
    return output


def solve_part2(input_, minutes=32):
    blueprints = transform_input(input_)
    output = 1
    for bp in blueprints[:3]:
        output *= solve(bp, minutes)
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 19")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day19/data/input.txt",
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
    "input1, output1", [("year2022/day19/data/test_input0.txt", 33)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day19/data/test_input0.txt", 108)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2), minutes=24) == output2
