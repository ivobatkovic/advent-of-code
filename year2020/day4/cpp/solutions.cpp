#include "year2020/day4/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.hpp"

namespace year2020 {

namespace day4 {

using namespace std;
using map_type = unordered_map<string, string>;
using input_type = vector<map_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    map_type passport{};
    for (string const &line : utils::split_string<string>(input_string, "\n")) {
        if (line.size() == 0) {
            output.push_back(passport);
            passport.clear();
            continue;
        }

        for (const string &entry : utils::split_string<string>(line, " ")) {
            auto const key_and_value = utils::split_string<string>(entry, ":");
            assert(key_and_value.size() == 2U);
            passport[key_and_value.front()] = key_and_value.back();
        }
    }
    output.push_back(passport);
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    array<string, 7U> fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    auto const is_valid = [&fields](map_type const &passport) {
        for (auto const &field : fields) {
            if (!passport.contains(field)) {
                return false;
            }
        }
        return true;
    };

    return to_string(accumulate(input.begin(), input.end(), 0U,
                                [&is_valid](size_t const acc, auto const &x) {
                                    return acc + is_valid(x);
                                }));
}

bool is_valid(const map_type &passport) {
    array<pair<string, boost::regex>, 7U> const regexes{
        make_pair("byr", boost::regex("^(19[2-9]\\d|200[0-2])$")),
        make_pair("iyr", boost::regex("^20(1\\d|20)$")),
        make_pair("eyr", boost::regex("^20(2\\d|30)$")),
        make_pair("hgt",
                  boost::regex("^(1([5-8]\\d|9[0-3])cm|(59|6\\d|7[0-6])in)$")),
        make_pair("hcl", boost::regex("^#[\\da-f]{6}$")),
        make_pair("ecl", boost::regex("^(amb|blu|brn|gry|grn|hzl|oth)$")),
        make_pair("pid", boost::regex("^\\d{9}$")),
    };

    for (auto const &[key, regex] : regexes) {
        if (!passport.contains(key) ||
            utils::regex_find_all<string>(passport.at(key), regex).size() ==
                0) {
            return false;
        }
    }
    return true;
}
std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    return to_string(accumulate(
        input.begin(), input.end(), 0U,
        [](size_t const acc, auto const &x) { return acc + is_valid(x); }));
}

}  // namespace day4

}  // namespace year2020
