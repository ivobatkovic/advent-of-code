#include "year2016/day4/cpp/solutions.hpp"

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

namespace year2016 {

namespace day4 {

using namespace std;
using input_type = vector<array<string, 3U>>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    boost::regex const regex("(.*)-(\\d+)\\[(\\w+)\\]$");

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const match = utils::regex_find_all<string>(line, regex);
        assert(match.size() == 4U);
        output.push_back({match.at(1U), match.at(2U), match.at(3U)});
    }
    return output;
}

bool is_valid_checksum(string const &letters, string const &checksum) {
    unordered_map<char, int32_t> counts{};

    for (auto const &chr : letters) {
        if (chr == '-') {
            continue;
        }
        if (counts.contains(chr)) {
            counts[chr]++;
        } else {
            counts[chr] = 1;
        }
    }

    string computed_checksum;
    for (auto &pair : counts) {
        computed_checksum += pair.first;
    }

    sort(computed_checksum.begin(), computed_checksum.end(),
         [&counts](char const a, char const b) {
             if (counts[a] != counts[b]) {
                 return counts[a] > counts[b];
             }
             return a < b;
         });

    return computed_checksum.substr(0U, 5U) == checksum;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    for (auto const &[letters, sector_id, checksum] : input) {
        output +=
            (is_valid_checksum(letters, checksum)) ? stoull(sector_id) : 0U;
    }
    return to_string(output);
}

bool shifted_letters_contain_northpole(const string &letters,
                                       int32_t const shift) {
    int32_t offset = 'a';
    int32_t max_val = 'z' - 'a' + 1;

    string output{};
    for (char letter : letters) {
        output +=
            static_cast<char>((letter - offset + shift) % max_val + offset);
    }

    return output.starts_with("northpole");
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    for (auto const &[letters, sector_id, checksum] : input) {
        if (is_valid_checksum(letters, checksum) &&
            shifted_letters_contain_northpole(letters, stoi(sector_id))) {
            return sector_id;
        }
    }
    return "0";
}

}  // namespace day4

}  // namespace year2016
