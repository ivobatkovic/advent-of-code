#include "year2015/day5/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2015 {

namespace day5 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    boost::regex const vowels("([aeiou].*){3,}");
    boost::regex const double_chars("(.)\\1");
    boost::regex const forbidden("ab|cd|pq|xy");

    auto const is_nice = [&vowels, &double_chars,
                          &forbidden](string const &word) {
        return boost::regex_search(word, vowels) &&
               boost::regex_search(word, double_chars) &&
               !boost::regex_search(word, forbidden);
    };

    return to_string(
        accumulate(input.begin(), input.end(), 0U,
                   [&is_nice](size_t const acc, string const &word) {
                       return acc + is_nice(word);
                   }));
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    boost::regex const non_overlapping_pair("(..).*\\1");
    boost::regex const one_character_inbetween("(.).\\1");

    auto const is_nice = [&non_overlapping_pair,
                          &one_character_inbetween](string const &word) {
        return boost::regex_search(word, non_overlapping_pair) &&
               boost::regex_search(word, one_character_inbetween);
    };

    return to_string(
        accumulate(input.begin(), input.end(), 0U,
                   [&is_nice](size_t const acc, string const &word) {
                       return acc + is_nice(word);
                   }));
}

}  // namespace day5

}  // namespace year2015
