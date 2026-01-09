#include "year2018/day4/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

namespace year2018 {

namespace day4 {

using namespace std;
using input_type = vector<pair<string, string>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    boost::regex regex("\\[(\\d{4}-\\d\\d-\\d\\d \\d\\d:\\d\\d)\\] (.*)$");

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        vector<string> match = utils::regex_find_all<string>(line, regex);
        assert(match.size() == 3U);
        output.push_back({match.at(1U), match.at(2U)});
    }

    std::sort(
        output.begin(), output.end(),
        [](auto const &lhs, auto const &rhs) { return lhs.first < rhs.first; });

    return output;
}

unordered_map<int32_t, array<int32_t, 60U>> compute_sleep_times(
    input_type const &input) {
    boost::regex const regex("\\d+");
    unordered_map<int32_t, array<int32_t, 60>> sleep_times{};
    int32_t current_guard{};

    for (size_t i{0U}; i < input.size(); ++i) {
        auto const &[date, instr] = input.at(i);

        if (instr.find("Guard") != std::string::npos) {
            current_guard =
                utils::regex_find_all<int32_t>(instr, regex).front();
            if (!sleep_times.contains(current_guard)) {
                sleep_times[current_guard] = array<int32_t, 60>{};
            }
        }

        if (instr.find("wakes") != std::string::npos) {
            string const &date_of_sleep = input.at(i - 1U).first;
            size_t const sleep_time =
                stoull(date_of_sleep.substr(date_of_sleep.size() - 2U));
            size_t const wake_time = stoull(date.substr(date.size() - 2U));

            for (size_t t{sleep_time}; t < wake_time; ++t) {
                sleep_times[current_guard].at(t)++;
            }
        }
    }
    return sleep_times;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    auto const sleep_times = compute_sleep_times(input);

    auto const sum_minutes = [](array<int32_t, 60> const &minutes) {
        return accumulate(minutes.begin(), minutes.end(), 0);
    };

    auto const &[guard, minutes] = *std::max_element(
        sleep_times.begin(), sleep_times.end(),
        [&sum_minutes](auto const &lhs, auto const &rhs) {
            return sum_minutes(lhs.second) < sum_minutes(rhs.second);
        });
    auto max_minute_it = std::max_element(minutes.begin(), minutes.end());
    int32_t minute =
        static_cast<int32_t>(std::distance(minutes.begin(), max_minute_it));

    return to_string(guard * minute);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    auto const sleep_times = compute_sleep_times(input);

    auto const max_minutes = [](array<int32_t, 60> const &minutes) {
        return *max_element(minutes.begin(), minutes.end());
    };

    auto const &[guard, minutes] = *std::max_element(
        sleep_times.begin(), sleep_times.end(),
        [&max_minutes](auto const &lhs, auto const &rhs) {
            return max_minutes(lhs.second) < max_minutes(rhs.second);
        });
    auto max_minute_it = std::max_element(minutes.begin(), minutes.end());
    int32_t minute =
        static_cast<int32_t>(std::distance(minutes.begin(), max_minute_it));

    return to_string(guard * minute);
}

}  // namespace day4

}  // namespace year2018
