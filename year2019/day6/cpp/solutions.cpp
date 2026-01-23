#include "year2019/day6/cpp/solutions.hpp"

#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2019 {

namespace day6 {

using namespace std;
using input_type = unordered_map<string, vector<string>>;

static input_type transform_input(const string &input_string) {
    input_type orbits{};

    for (auto const &connections :
         utils::split_string<string>(input_string, "\n")) {
        auto const connection = utils::split_string<string>(connections, ")");
        assert(connection.size() == 2U);
        orbits[connection.front()].push_back(connection.back());
        orbits[connection.back()].push_back(connection.front());
    }
    return orbits;
}

std::string solve_part1(const string &input_string) {
    auto const &orbits = transform_input(input_string);

    std::deque<pair<string, size_t>> queue{};
    queue.push_back({"COM", 0});

    unordered_set<string> visited{};
    size_t output{};
    while (!queue.empty()) {
        auto const &[src, depth] = queue.front();
        queue.pop_front();

        if (visited.contains(src)) {
            continue;
        }
        visited.insert(src);
        output += depth;

        for (auto const &keys : orbits.at(src)) {
            queue.push_back({keys, depth + 1});
        }
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto const orbits = transform_input(input_string);

    std::deque<pair<string, size_t>> queue{{"YOU", 0}};

    unordered_set<string> visited{};
    while (!queue.empty()) {
        auto const &[src, depth] = queue.front();
        queue.pop_front();

        if (src == "SAN") {
            return to_string(depth - 2U);
        } else if (visited.contains(src)) {
            continue;
        }

        visited.insert(src);

        for (auto const &keys : orbits.at(src)) {
            queue.push_back({keys, depth + 1});
        }
    }
    return "0";
}

}  // namespace day6

}  // namespace year2019
