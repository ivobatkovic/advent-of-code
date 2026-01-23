#include "year2023/day6/cpp/solutions.hpp"

#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2023 {

namespace day6 {

using namespace std;

using numbers_type = vector<string>;
using input_type = pair<numbers_type, numbers_type>;

static input_type transform_input(const string &input_string) {
    auto const split = utils::split_string<string>(input_string, "\n");
    assert(split.size() == 2U);

    return make_pair(
        utils::regex_find_all<string>(split.front(), boost::regex("\\d+")),
        utils::regex_find_all<string>(split.back(), boost::regex("\\d+")));
}

int64_t compute(int64_t const duration, int64_t const distance) {
    int64_t stop_duration{duration - 1};
    while (true) {
        if (stop_duration * (duration - stop_duration) > distance) {
            break;
        }
        --stop_duration;
    }

    int64_t start_duration{1};
    while (true) {
        if (start_duration * (duration - start_duration) > distance) {
            break;
        }
        ++start_duration;
    }

    return stop_duration - start_duration + 1;
}

std::string solve_part1(const string &input_string) {
    auto const &[durations, distances] = transform_input(input_string);

    int64_t output{1U};

    for (size_t i{0U}; i < durations.size(); ++i) {
        output *=
            compute(std::stoi(durations.at(i)), std::stoi(distances.at(i)));
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto const &[durations, distances] = transform_input(input_string);

    string duration;
    string distance;

    for (size_t i{0U}; i < durations.size(); ++i) {
        duration += durations.at(i);
        distance += distances.at(i);
    }
    return to_string(compute(std::stol(duration), std::stol(distance)));
}

}  // namespace day6

}  // namespace year2023
