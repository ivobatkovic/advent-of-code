#include "year2023/day2/cpp/solutions.hpp"

#include <array>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2023 {

namespace day2 {

using namespace std;

using rgb_type = array<int64_t, 3U>;
using game_type = vector<rgb_type>;
using input_type = vector<game_type>;

static input_type transform_input(const string &input_string) {
    input_type games{};
    for (auto const &line : utils::split_string<string>(input_string, "\n")) {
        game_type game{};
        for (auto const &subset : utils::split_string<string>(line, ";")) {
            rgb_type rgb{};
            for (auto const &match : utils::regex_find_all<string>(
                     subset, boost::regex("\\d+ \\w+"))) {
                auto const val_and_color =
                    utils::split_string<string>(match, " ");
                int64_t val = stoi(val_and_color.front());
                string const color = val_and_color.back();

                if (color == "red") {
                    rgb.at(0U) = val;
                } else if (color == "green") {
                    rgb.at(1U) = val;
                } else if (color == "blue") {
                    rgb.at(2U) = val;
                }
            }
            game.push_back(rgb);
        }
        games.push_back(game);
    }
    return games;
}
std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    size_t output{};

    for (size_t i{0U}; i < input.size(); ++i) {
        bool possible{true};
        for (auto const &[r, g, b] : input.at(i)) {
            if (r > 12 || g > 13 || b > 14) {
                possible = false;
                break;
            }
        }

        output += (possible) ? i + 1U : 0;
    }
    return to_string(output);
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    int64_t output{};

    for (size_t i{0U}; i < input.size(); ++i) {
        int64_t R{}, G{}, B{};
        for (auto const &[r, g, b] : input.at(i)) {
            R = max(R, r);
            G = max(G, g);
            B = max(B, b);
        }

        output += R * G * B;
    }
    return to_string(output);
}

}  // namespace day2

}  // namespace year2023
