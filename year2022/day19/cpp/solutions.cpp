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

queue_t limitStates(queue_t const &state, std::size_t const max_ore_cost,
                    std::size_t const clay_cost_obs,
                    std::size_t const obs_cost_geo) {
    auto [o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t] = state;

    ore_r = (ore_r >= max_ore_cost) ? max_ore_cost : ore_r;
    clay_r = (clay_r >= clay_cost_obs) ? clay_cost_obs : clay_r;
    obs_r = (obs_r >= obs_cost_geo) ? obs_cost_geo : obs_r;
    if (o >= t * max_ore_cost - ore_r * (t - 1)) {
        o = t * max_ore_cost - ore_r * (t - 1);
    }
    if (c >= t * clay_cost_obs - clay_r * (t - 1)) {
        c = t * clay_cost_obs - clay_r * (t - 1);
    }
    if (ob >= t * obs_cost_geo - obs_r * (t - 1)) {
        ob = t * obs_cost_geo - obs_r * (t - 1);
    }
    return {o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t};
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
        state = q.front();
        q.pop();
        max_geodes = max(max_geodes, state.at(3U));

        if (state.back() == 0) {
            continue;
        }

        state = limitStates(state, max_ore_cost, clay_cost_obs, obs_cost_geo);

        if (visited.count(state)) {
            continue;
        }
        visited.insert(state);

        auto &[o, c, ob, g, ore_r, clay_r, obs_r, geo_r, t] = state;

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
    for (std::size_t idx{0U}; idx < std::min(size_t{3U}, blueprints.size());
         ++idx) {
        output *= solve(blueprints[idx], minutes);
    }
    return to_string(output);
}

}  // namespace day19

}  // namespace year2022
