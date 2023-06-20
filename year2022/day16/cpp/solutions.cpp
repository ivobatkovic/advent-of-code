#include "year2022/day16/cpp/solutions.hpp"

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day16 {

using namespace std;
using distance_type = map<pair<string, string>, int>;
using flows_type = map<string, int>;
using bitmask_type = map<string, int>;
using input_type = tuple<distance_type, flows_type, bitmask_type>;

int compute_distance(string const &start_valve, string const &goal_valve,
                     map<string, vector<string>> const &connections) {
    queue<tuple<string, int, set<string>>> node;
    node.push(make_tuple(start_valve, 0, set<string>{}));
    while (node.size() > 0) {
        auto [valve, dist, visited] = node.front();
        node.pop();
        if (valve == goal_valve) {
            return dist;
        }
        for (auto &next_valve : connections.at(valve)) {
            if (!visited.count(next_valve)) {
                set<string> vi(visited);
                vi.insert(valve);
                node.push(make_tuple(next_valve, dist + 1, vi));
            }
        }
    }
    return 1000;
}

static input_type transform_input(const std::string &input_string) {
    map<string, vector<string>> connections{};
    flows_type flows{};
    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto valves = utils::regex_find_all<string>(row, regex("[A-Z][A-Z]"));
        for (size_t i{1U}; i < valves.size(); ++i) {
            connections[valves[0]].push_back(valves[i]);
        }
        int flow = utils::regex_find_all<int>(row, regex("\\d+"))[0];
        if (flow != 0) {
            flows[valves[0]] = flow;
        }
    }

    vector<string> valves_to_open{"AA"};
    for (auto &[valve, flow] : flows) {
        valves_to_open.push_back(valve);
    }

    distance_type distance_connections{};
    for (auto &i : valves_to_open) {
        for (auto &j : valves_to_open) {
            auto distance = compute_distance(i, j, connections);
            distance_connections[{i, j}] = distance;
            distance_connections[{j, i}] = distance;
        }
    }

    bitmask_type bitmask{};
    int i = 0;
    for (auto const &x : flows) {
        bitmask[x.first] = 1 << i++;
    }
    return {distance_connections, flows, bitmask};
}

std::string solve_part1(const std::string &input_string) {
    auto [dist, flows, bitmask] = transform_input(input_string);

    const function<void(string, int, int, int, map<int, int> &)> visit =
        [&visit, &flows = flows, &bitmask = bitmask, &dist = dist](
            string valve, int minute, int pressure, int open_valves,
            map<int, int> &pressure_paths) {
            if (pressure_paths.count(open_valves)) {
                pressure_paths[open_valves] =
                    max(pressure_paths[open_valves], pressure);
            } else {
                pressure_paths[open_valves] = pressure;
            }
            for (auto &[next_valve, flow] : flows) {
                auto remaining_minutes = minute - dist[{valve, next_valve}] - 1;
                if (bitmask[next_valve] & open_valves ||
                    remaining_minutes <= 0) {
                    continue;
                }
                visit(next_valve, remaining_minutes,
                      pressure + remaining_minutes * flow,
                      open_valves | bitmask[next_valve], pressure_paths);
            }
            return;
        };

    map<int, int> paths;
    visit("AA", 30, 0, 0, paths);
    auto best_path = max_element(
        paths.begin(), paths.end(),
        [](auto const &l, auto const &r) { return l.second < r.second; });
    return to_string(best_path->second);
}

std::string solve_part2(const std::string &input_string) {
    auto [dist, flows, bitmask] = transform_input(input_string);

    const function<void(string, int, int, int, map<int, int> &)> visit =
        [&visit, &flows = flows, &bitmask = bitmask, &dist = dist](
            string valve, int minute, int pressure, int open_valves,
            map<int, int> &pressure_paths) {
            if (pressure_paths.count(open_valves)) {
                pressure_paths[open_valves] =
                    max(pressure_paths[open_valves], pressure);
            } else {
                pressure_paths[open_valves] = pressure;
            }
            for (auto &[next_valve, flow] : flows) {
                auto remaining_minutes = minute - dist[{valve, next_valve}] - 1;
                if (bitmask[next_valve] & open_valves ||
                    remaining_minutes <= 0) {
                    continue;
                }
                visit(next_valve, remaining_minutes,
                      pressure + remaining_minutes * flow,
                      open_valves | bitmask[next_valve], pressure_paths);
            }
            return;
        };

    map<int, int> paths;
    visit("AA", 26, 0, 0, paths);

    int max_pressure = 0;
    for (auto [bitmask1, pressure1] : paths) {
        for (auto [bitmask2, pressure2] : paths) {
            if ((bitmask1 & bitmask2) == 0) {
                max_pressure = max(max_pressure, pressure1 + pressure2);
            }
        }
    }
    return to_string(max_pressure);
}

}  // namespace day16

}  // namespace year2022
