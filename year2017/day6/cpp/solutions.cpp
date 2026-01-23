#include "year2017/day6/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

struct VectorHash {
    std::size_t operator()(const std::vector<size_t> &v) const noexcept {
        std::size_t seed = v.size();
        for (size_t x : v) {
            seed ^= std::hash<size_t>{}(x) + 0x9e3779b97f4a7c15ULL +
                    (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

namespace year2017 {

namespace day6 {

using namespace std;
using input_type = vector<size_t>;
using set_type = unordered_set<input_type, VectorHash>;

static input_type transform_input(const string &input_string) {
    return utils::regex_find_all<size_t>(input_string, boost::regex("\\d+"));
}

void redistribute(input_type &memory) {
    auto it = std::max_element(memory.begin(), memory.end());
    size_t max_val = *it;
    size_t idx = static_cast<size_t>(std::distance(memory.begin(), it));
    size_t n = memory.size();

    memory.at(idx) = 0;
    for (size_t i{0U}; i < max_val; ++i) {
        memory.at((idx + i + 1) % n)++;
    }
}

std::string solve_part1(const string &input_string) {
    input_type memory = transform_input(input_string);
    set_type visited{};

    size_t count{};

    while (true) {
        if (visited.contains(memory)) {
            return to_string(count);
        }

        visited.insert(memory);
        redistribute(memory);
        count++;
    }
}

std::string solve_part2(const string &input_string) {
    input_type memory = transform_input(input_string);
    input_type revisited{};
    set_type visited{};

    while (true) {
        if (visited.contains(memory)) {
            revisited = memory;
            break;
        }

        visited.insert(memory);
        redistribute(memory);
    }

    size_t count{};
    while (true) {
        redistribute(memory);
        count++;

        if (revisited == memory) {
            return to_string(count);
        }
    }
}

}  // namespace day6

}  // namespace year2017
