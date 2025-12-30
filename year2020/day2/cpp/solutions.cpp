#include "year2020/day2/cpp/solutions.hpp"

#include <numeric>
#include <string>
#include <tuple>
#include <vector>

#include "utils/utils.hpp"

namespace year2020 {

namespace day2 {

using namespace std;

using database_type = tuple<int32_t, int32_t, char, string>;
using input_type = vector<database_type>;

static input_type transform_input(const string &input_string) {
    input_type output{};

    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        auto const range =
            utils::regex_find_all<string>(line, boost::regex("(\\d+)-(\\d+)"));
        auto const letter =
            utils::regex_find_all<char>(line, boost::regex("([a-z]):"));
        auto const password =
            utils::regex_find_all<string>(line, boost::regex(": (\\w+)"));

        output.push_back(make_tuple(stoi(range.at(1U)), stoi(range.back()),
                                    letter.at(1U), password.at(1U)));
    }
    return output;
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    auto const valid = [](int32_t acc, database_type x) {
        auto const &[low, hi, letter, password] = x;
        auto count = std::count(password.begin(), password.end(), letter);
        return (count >= low and count <= hi) ? acc + 1 : acc + 0;
    };

    return to_string(accumulate(input.begin(), input.end(), 0, valid));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    auto const valid = [](int32_t acc, database_type x) {
        auto const &[low, hi, letter, password] = x;
        return ((letter == password.at(static_cast<size_t>(low - 1))) ^
                (letter == password.at(static_cast<size_t>(hi - 1))))
                   ? acc + 1
                   : acc + 0;
    };

    return to_string(accumulate(input.begin(), input.end(), 0, valid));
}

}  // namespace day2

}  // namespace year2020
