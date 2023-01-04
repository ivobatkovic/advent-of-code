#include "year2022/day13/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day13 {

using namespace std;
using input_type = vector<string>;

vector<string> split_packet(string const &packet) {
    vector<string> output;
    size_t depth{};
    string tmp;
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

static input_type transform_input(const string &input_string) {
    input_type pairs{};
    for (auto pair : utils::split_string<string>(input_string, "\n\n")) {
        for (auto packet : utils::split_string<string>(pair, "\n")) {
            pairs.push_back(packet);
        }
    }
    return pairs;
}

int compare(vector<string> const &left, vector<string> const &right) {
    for (size_t i{0U}; i < min(left.size(), right.size()); ++i) {
        if (left[i][0] != '[' && right[i][0] != '[') {
            int diff = stoi(left[i]) - stoi(right[i]);
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

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    int tot = 0;
    for (size_t i = 0; i < input.size() / 2; ++i) {
        if (compare(split_packet(input[2 * i]),
                    split_packet(input[2 * i + 1])) < 0) {
            tot += (static_cast<int>(i) + 1);
        }
    }
    return to_string(tot);
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string + "\n[[2]]\n[[6]]");
    sort(input.begin(), input.end(), [](string s1, string s2) {
        return compare(split_packet(s1), split_packet(s2)) < 0;
    });
    auto find_index = [](vector<string> s, string match) {
        return find(s.begin(), s.end(), match) - s.begin() + 1;
    };
    return to_string(find_index(input, "[[2]]") * find_index(input, "[[6]]"));
}

}  // namespace day13

}  // namespace year2022
