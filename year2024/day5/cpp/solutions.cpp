#include "year2024/day5/cpp/solutions.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace year2024 {

namespace day5 {

using namespace std;
using set_type = unordered_set<int32_t>;
using rules_type = unordered_map<int32_t, set_type>;
using pages_type = vector<int32_t>;
using input_type = pair<rules_type, vector<pages_type>>;

static input_type transform_input(const string &input_string) {
    vector<string> split = utils::split_string<string>(input_string, "\n\n");
    assert(split.size() == 2U);

    auto const rules_string = split.front();
    auto const pages_string = split.back();

    rules_type rules{};

    boost::regex const regex("\\d+");
    for (auto const &rule : utils::split_string<string>(rules_string, "\n")) {
        auto const numbers = utils::regex_find_all<int32_t>(rule, regex);
        assert(numbers.size() == 2U);
        rules[numbers.front()].insert(numbers.back());
    }

    vector<pages_type> pages{};
    for (auto const &line : utils::split_string<string>(pages_string, "\n")) {
        pages.push_back(utils::regex_find_all<int32_t>(line, regex));
    }

    return {rules, pages};
}

bool check_pages(rules_type &rules, pages_type const &pages) {
    for (size_t i{0U}; i < pages.size() - 1U; ++i) {
        auto const &page = pages.at(i);
        for (size_t j{i + 1U}; j < pages.size(); ++j) {
            if (rules[pages.at(j)].contains(page)) {
                return false;
            }
        }
    }
    return true;
}

std::string solve_part1(const string &input_string) {
    auto [rules, list_of_pages] = transform_input(input_string);

    int32_t output{};
    for (auto const &pages : list_of_pages) {
        if (check_pages(rules, pages)) {
            output += pages.at(pages.size() / 2);
        }
    }
    return to_string(output);
}

bool is_page_first(int32_t const page, set_type const &other_pages,
                   rules_type const &rules) {
    for (auto const &other_page : other_pages) {
        if (rules.at(other_page).contains(page)) {
            return false;
        }
    }
    return true;
}

pages_type fix_pages(rules_type const &rules, pages_type const &pages) {
    pages_type output{};

    set_type pages_to_consider(pages.begin(), pages.end());
    while (pages_to_consider.size()) {
        for (auto const &page : pages_to_consider) {
            if (is_page_first(page, pages_to_consider, rules)) {
                output.push_back(page);
                pages_to_consider.erase(page);
                break;
            }
        }
    }
    return output;
}

std::string solve_part2(const string &input_string) {
    auto [rules, list_of_pages] = transform_input(input_string);

    int32_t output{};
    for (auto &pages : list_of_pages) {
        if (!check_pages(rules, pages)) {
            pages = fix_pages(rules, pages);
            output += pages.at(pages.size() / 2);
        }
    }
    return to_string(output);
}

}  // namespace day5

}  // namespace year2024
