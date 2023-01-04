#include "year2022/day11/cpp/solutions.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day11 {

using namespace std;
using input_type = vector<string>;

class Monkey {
   public:
    Monkey(string const &input) {
        auto rows = utils::split_string<string>(input, "\n");
        items_ = utils::regex_find_all<size_t>(rows[1], regex("\\d+"));

        auto regexp = regex("\\d+");
        operand_ = utils::regex_find_all<size_t>(rows[2], regexp);
        if (rows[2].find('+') != string::npos) {
            operation_ = '+';
        } else if (rows[2].find('-') != string::npos) {
            operation_ = '-';
        } else if (rows[2].find('*') != string::npos) {
            operation_ = '*';
        } else {
            operation_ = '/';
        }

        divisable_ = utils::regex_find_all<size_t>(rows[3], regexp)[0];
        true_test_ = utils::regex_find_all<size_t>(rows[4], regexp)[0];
        false_test_ = utils::regex_find_all<size_t>(rows[5], regexp)[0];
    }

    size_t operation(size_t k) {
        auto val = (operand_.size()) ? operand_.front() : k;
        if (operation_ == '+') {
            return k + val;
        } else if (operation_ == '-') {
            return k - val;
        } else if (operation_ == '*') {
            return k * val;
        } else {
            return k / val;
        }
    }

    size_t test(size_t k) {
        return (k % divisable_ == 0) ? true_test_ : false_test_;
    }

    vector<size_t> items_{};
    vector<size_t> operand_{};
    char operation_{};
    size_t divisable_{};
    size_t true_test_{};
    size_t false_test_{};
    size_t processed_{};
};

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n\n");
}

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    vector<Monkey> monkeys;
    for (auto &row : input) {
        monkeys.push_back(Monkey(row));
    }

    for (size_t k{0U}; k < 20U; ++k) {
        for (auto &monkey : monkeys) {
            while (monkey.items_.size()) {
                auto item = monkey.items_.front();
                monkey.items_.erase(monkey.items_.begin());
                monkey.processed_++;
                item = monkey.operation(item) / 3U;
                monkeys[monkey.test(item)].items_.push_back(item);
            }
        }
    }

    vector<size_t> p;
    for (auto &monkey : monkeys) {
        p.push_back(monkey.processed_);
    }
    sort(p.begin(), p.end(), greater<size_t>());
    return to_string(p[0] * p[1]);
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    vector<Monkey> monkeys;
    size_t monkeymod{1U};
    for (auto &row : input) {
        monkeys.push_back(Monkey(row));
        monkeymod *= monkeys.back().divisable_;
    }

    for (size_t k{0U}; k < 10000U; ++k) {
        for (auto &monkey : monkeys) {
            while (monkey.items_.size()) {
                auto item = monkey.items_.front();
                monkey.items_.erase(monkey.items_.begin());
                monkey.processed_++;
                item = monkey.operation(item) % monkeymod;
                monkeys[monkey.test(item)].items_.push_back(item);
            }
        }
    }

    vector<size_t> p;
    for (auto &monkey : monkeys) {
        p.push_back(monkey.processed_);
    }
    sort(p.begin(), p.end(), greater<size_t>());
    return to_string(p[0] * p[1]);
}

}  // namespace day11

}  // namespace year2022
