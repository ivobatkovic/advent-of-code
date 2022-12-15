#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day6/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day6 {

class TestYear2022Day6PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day6PartOne, PartOne) {
    auto param = GetParam();
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day6::solve_part1(std::get<0>(param)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOne, TestYear2022Day6PartOne,
    ::testing::Values(
        std::make_tuple("mjqjpqmgbljsphdztnvjfqwrcgsmlb", "7"),
        std::make_tuple("bvwbjplbgvbhsrlpgdmjqwftvncz", "5"),
        std::make_tuple("nppdvjthqldpwncqszvftbrmjlhg", "6"),
        std::make_tuple("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", "10"),
        std::make_tuple("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", "11")));

class TestYear2022Day6PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day6PartTwo, PartTwo) {
    auto param = GetParam();
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day6::solve_part2(std::get<0>(param)));
}

INSTANTIATE_TEST_SUITE_P(
    PartTwo, TestYear2022Day6PartTwo,
    ::testing::Values(
        std::make_tuple("mjqjpqmgbljsphdztnvjfqwrcgsmlb", "19"),
        std::make_tuple("bvwbjplbgvbhsrlpgdmjqwftvncz", "23"),
        std::make_tuple("nppdvjthqldpwncqszvftbrmjlhg", "23"),
        std::make_tuple("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", "29"),
        std::make_tuple("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", "26")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day6

}  // namespace year2022
