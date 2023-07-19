#include "year2022/day21/cpp/solutions.hpp"

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day21 {

using namespace std;
using input_type = map<string, array<string, 3U>>;

static input_type transform_input(const string &input_string) {
    input_type tree{};

    regex name_pattern{"\\w+|\\d+"};
    regex op_pattern{"\\+|\\-|\\/|\\*"};
    for (auto row : utils::split_string<string>(input_string, "\n")) {
        auto operands = utils::regex_find_all<string>(row, name_pattern);
        auto operation = utils::regex_find_all<string>(row, op_pattern);

        if (operation.size() > 0U) {
            tree[operands.at(0U)] = {operation.at(0U), operands.at(1U),
                                     operands.at(2U)};
        } else {
            tree[operands.at(0U)] = {"", operands.at(1U), "0"};
        }
    }
    return tree;
}

int64_t compute(input_type const &x, string const &name) {
    if (isdigit(name.at(0U))) {
        return stoi(name);
    }

    auto &[operation, val1, val2] = x.at(name);
    if (operation == "+") {
        return compute(x, val1) + compute(x, val2);
    } else if (operation == "-") {
        return compute(x, val1) - compute(x, val2);
    } else if (operation == "*") {
        return compute(x, val1) * compute(x, val2);
    } else if (operation == "/") {
        return compute(x, val1) / compute(x, val2);
    }
    return compute(x, val1);
}

int64_t reverse_operation(string const &operation, int64_t const val1,
                          int64_t const val2, bool left_op = true) {
    // Solve for x, where
    // val1 = x [+|-|/|*] val2 if left_op, otherwise
    // val1 = val2 [+|-|/|*] x
    if (operation == "+") {
        return val1 - val2;
    } else if (operation == "-") {
        return (left_op) ? val1 + val2 : val2 - val1;
    } else if (operation == "*") {
        return val1 / val2;
    } else {
        return (left_op) ? val1 * val2 : val2 / val1;
    }
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    return std::to_string(compute(input, "root"));
}

bool check_dependency(input_type const &x, string const &name,
                      string const &target) {
    if (name == target) {
        return true;
    }
    auto &[operation, val1, val2] = x.at(name);
    if (operation.size() > 0U) {
        return check_dependency(x, val1, target) ||
               check_dependency(x, val2, target);
    }
    return false;
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    string head = "root";
    int64_t value{0U};
    int64_t tmp_value{0U};

    while (head != "humn") {
        size_t depends_on_val1 =
            (check_dependency(input, input.at(head).at(1U), "humn")) ? 1 : 0;
        tmp_value = compute(input, input.at(head).at(1U + depends_on_val1));
        if (head == "root") {
            value = tmp_value;
        } else {
            value = reverse_operation(input.at(head).at(0U), value, tmp_value,
                                      depends_on_val1);
        }
        head = input.at(head).at(2U - depends_on_val1);
    }
    return to_string(value);
}

}  // namespace day21

}  // namespace year2022
