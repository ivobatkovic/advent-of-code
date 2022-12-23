#include "year2022/day11/cpp/solutions.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day11 {

using input_type = std::vector<std::string>;

class Monkey {
   public:
    Monkey(std::string const &input) {
        auto rows = utils::split_string<std::string>(input, "\n");
        items_ = utils::regex_find_all<size_t>(rows[1], std::regex("\\d+"));

        auto regexp = std::regex("\\d+");
        operand_ = utils::regex_find_all<size_t>(rows[2], regexp);
        if (rows[2].find('+') != std::string::npos) {
            operation_ = '+';
        } else if (rows[2].find('-') != std::string::npos) {
            operation_ = '-';
        } else if (rows[2].find('*') != std::string::npos) {
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

    std::vector<size_t> items_{};
    std::vector<size_t> operand_{};
    char operation_{};
    size_t divisable_{};
    size_t true_test_{};
    size_t false_test_{};
    size_t processed_{};
};

static input_type transform_input(const std::string &input_string) {
    return utils::split_string<std::string>(input_string, "\n\n");
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);

    std::vector<Monkey> monkeys;
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

    std::vector<size_t> p;
    for (auto &monkey : monkeys) {
        p.push_back(monkey.processed_);
    }
    std::sort(p.begin(), p.end(), std::greater<size_t>());
    return std::to_string(p[0] * p[1]);
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);

    std::vector<Monkey> monkeys;
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

    std::vector<size_t> p;
    for (auto &monkey : monkeys) {
        p.push_back(monkey.processed_);
    }
    std::sort(p.begin(), p.end(), std::greater<size_t>());
    return std::to_string(p[0] * p[1]);
}

}  // namespace day11

}  // namespace year2022
