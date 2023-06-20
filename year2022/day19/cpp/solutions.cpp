#include "year2022/day19/cpp/solutions.hpp"

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day19 {

using namespace std;
using input_type = vector<string>;
using queue_t = array<size_t, 9U>;
using blueprint_t = array<size_t, 6U>;
using output_type = vector<blueprint_t>;

static output_type transform_input(const string &input_string) {
    vector<blueprint_t> blueprints{};
    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto matches = utils::regex_find_all<size_t>(row, regex("\\d+"));
        blueprint_t blueprint{};
        copy_n(matches.begin() + 1U, 6U, blueprint.begin());
        blueprints.push_back(blueprint);
    }
    return blueprints;
}

std::size_t solve(blueprint_t const &cost, const std::size_t minutes) {
    auto const &[ore_cost, clay_cost, ore_cost_obs, clay_cost_obs, ore_cost_geo,
                 obs_cost_geo] = cost;

    std::size_t max_geodes{0U};

    queue_t state{0, 0, 0, 0, 1, 0, 0, 0, minutes};
    queue<queue_t> q;
    q.push(state);

    std::set<queue_t> visited{};

    std::array<size_t, 4U> ore_costs{ore_cost, clay_cost, ore_cost_obs,
                                     ore_cost_geo};
    std::size_t const max_ore_cost{
        *max_element(ore_costs.begin(), ore_costs.end())};

    while (q.size() > 0) {
        auto [o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t] = q.front();
        q.pop();

        max_geodes = max(max_geodes, g);

        if (t == 0) {
            continue;
        }

        // Can only make one robot per time instance. Having more
        // ore/clay/obsidian robots than what it costs to make an upgrade does
        // not help.
        if (ore_r >= max_ore_cost) {
            ore_r = max_ore_cost;
        }
        if (clay_r >= clay_cost_obs) {
            clay_r = clay_cost_obs;
        }
        if (obs_r >= obs_cost_geo) {
            obs_r = obs_cost_geo;
        }
        // Same with number of ores - we can ignore ores that will never be used
        if (o >= t * max_ore_cost - ore_r * (t - 1)) {
            o = t * max_ore_cost - ore_r * (t - 1);
        }
        if (c >= t * clay_cost_obs - clay_r * (t - 1)) {
            c = t * clay_cost_obs - clay_r * (t - 1);
        }
        if (ob >= t * obs_cost_geo - obs_r * (t - 1)) {
            ob = t * obs_cost_geo - obs_r * (t - 1);
        }

        // Limited state space - helps with caching
        state =
            std::array<size_t, 9U>{o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t};
        if (visited.count(state)) {
            continue;
        }
        visited.insert(state);

        // Step without buying robot
        q.push({o + ore_r, c + clay_r, ob + obs_r, g + geo_r, ore_r, clay_r,
                obs_r, geo_r, t - 1});

        // Buy ore robot
        if (o >= ore_cost) {
            q.push({o - ore_cost + ore_r, c + clay_r, ob + obs_r, g + geo_r,
                    ore_r + 1, clay_r, obs_r, geo_r, t - 1});
        }
        // Buy clay robot
        if (o >= clay_cost) {
            q.push({o - clay_cost + ore_r, c + clay_r, ob + obs_r, g + geo_r,
                    ore_r, clay_r + 1, obs_r, geo_r, t - 1});
        }
        // Buy obsidian robot
        if (o >= ore_cost_obs and c >= clay_cost_obs) {
            q.push({o - ore_cost_obs + ore_r, c - clay_cost_obs + clay_r,
                    ob + obs_r, g + geo_r, ore_r, clay_r, obs_r + 1, geo_r,
                    t - 1});
        }
        // Buy geode robot
        if (o >= ore_cost_geo and ob >= obs_cost_geo) {
            q.push({o - ore_cost_geo + ore_r, c + clay_r,
                    ob - obs_cost_geo + obs_r, g + geo_r, ore_r, clay_r, obs_r,
                    geo_r + 1, t - 1});
        }
    }
    return max_geodes;
}

string solve_part1(const string &input_string, const std::size_t minutes) {
    auto blueprints = transform_input(input_string);
    std::size_t output = 0U;
    for (std::size_t idx{0U}; idx < blueprints.size(); ++idx) {
        output += (idx + 1U) * solve(blueprints[idx], minutes);
    }
    return to_string(output);
}

string solve_part2(const string &input_string, const std::size_t minutes) {
    auto blueprints = transform_input(input_string);
    std::size_t output = 1U;
    for (std::size_t idx{0U}; idx < 3U; ++idx) {
        output *= solve(blueprints[idx], minutes);
    }
    return to_string(output);
}

}  // namespace day19

}  // namespace year2022
