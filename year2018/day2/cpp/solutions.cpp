#include "year2018/day2/cpp/solutions.hpp"

#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2018 {

namespace day2 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t twice{}, thrice{};

    for (auto const &id : input) {
        bool twice_found{false};
        bool thrice_found{false};

        unordered_set<char> seen{};
        for (auto const &chr : id) {
            if (seen.contains(chr)) {
                continue;
            }
            seen.insert(chr);

            size_t const count =
                static_cast<size_t>(std::count(id.begin(), id.end(), chr));

            if (count == 2 && !twice_found) {
                twice_found = true;
                twice += 1U;
            } else if (count == 3 && !thrice_found) {
                thrice_found = true;
                thrice += 1U;
            }
        }
    }
    return to_string(twice * thrice);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    for (size_t i{0U}; i < input.size() - 1; ++i) {
        for (size_t j{i + 1}; j < input.size(); ++j) {
            vector<size_t> indices{};
            for (size_t k{0U}; k < input.at(i).size(); ++k) {
                if (input.at(i).at(k) != input.at(j).at(k)) {
                    indices.push_back(k);
                }
            }

            if (indices.size() == 1U) {
                string output{input.at(i)};
                output.erase(indices.front(), 1);
                return output;
            }
        }
    }

    return "";
}

}  // namespace day2

}  // namespace year2018
