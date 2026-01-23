#include "year2016/day6/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

namespace year2016 {

namespace day6 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

string decode(input_type const &lines, bool const most_common = true) {
    string output{};

    auto const comp = [](const pair<char, size_t> &a,
                         const pair<char, size_t> &b) {
        return a.second < b.second;
    };

    for (size_t col{0U}; col < lines.at(0U).size(); ++col) {
        unordered_map<char, size_t> frequency{};
        for (size_t row{0U}; row < lines.size(); ++row) {
            frequency[lines.at(row).at(col)]++;
        }

        auto it =
            (most_common)
                ? std::max_element(frequency.begin(), frequency.end(), comp)
                : std::min_element(frequency.begin(), frequency.end(), comp);
        output += it->first;
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    return decode(input);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    return decode(input, false);
}

}  // namespace day6

}  // namespace year2016
