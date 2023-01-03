#include "year2022/day13/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day13 {

using input_type = std::vector<std::string>;

std::vector<std::string> split_packet(std::string const &packet) {
    std::vector<std::string> output;
    size_t depth{};
    std::string tmp;
    for (auto &x : packet.substr(1, packet.size() - 2)) {
        if (x == '[') {
            depth++;
        } else if (x == ']') {
            depth--;
        } else if (x == ',' && depth == 0) {
            output.push_back(tmp);
            tmp.clear();
        }

        if (x != ',' || (x == ',' && depth > 0)) {
            tmp += x;
        }
    }
    if (tmp.size() > 0) {
        output.push_back(tmp);
    }
    return output;
}

static input_type transform_input(const std::string &input_string) {
    input_type pairs{};
    for (auto pair : utils::split_string<std::string>(input_string, "\n\n")) {
        for (auto packet : utils::split_string<std::string>(pair, "\n")) {
            pairs.push_back(packet);
        }
    }
    return pairs;
}

int compare(std::vector<std::string> const &left,
            std::vector<std::string> const &right) {
    for (size_t i{0U}; i < std::min(left.size(), right.size()); ++i) {
        if (left[i][0] != '[' && right[i][0] != '[') {
            int diff = std::stoi(left[i]) - std::stoi(right[i]);
            if (diff != 0) {
                return diff;
            }
        }
        int x = 0;
        if (left[i][0] == '[' && right[i][0] != '[') {
            x = compare(split_packet(left[i]),
                        split_packet("[" + right[i] + "]"));
        } else if (left[i][0] != '[' && right[i][0] == '[') {
            x = compare(split_packet("[" + left[i] + "]"),
                        split_packet(right[i]));
        } else {
            x = compare(split_packet(left[i]), split_packet(right[i]));
        }
        if (x != 0) {
            return x;
        }
    }

    return static_cast<int>(left.size() - right.size());
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);
    int tot = 0;
    for (size_t i = 0; i < input.size() / 2; ++i) {
        if (compare(split_packet(input[2 * i]),
                    split_packet(input[2 * i + 1])) < 0) {
            tot += (static_cast<int>(i) + 1);
        }
    }
    return std::to_string(tot);
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string + "\n[[2]]\n[[6]]");
    std::sort(input.begin(), input.end(), [](std::string s1, std::string s2) {
        return compare(split_packet(s1), split_packet(s2)) < 0;
    });
    auto find_index = [](std::vector<std::string> s, std::string match) {
        return std::find(s.begin(), s.end(), match) - s.begin() + 1;
    };
    return std::to_string(find_index(input, "[[2]]") *
                          find_index(input, "[[6]]"));
}

}  // namespace day13

}  // namespace year2022
