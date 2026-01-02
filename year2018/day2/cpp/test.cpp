#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2018/day2/cpp/solutions.hpp"

using std::string;

namespace year2018 {

namespace day2 {

class TestYear2018Day2PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2018Day2PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2018/day2/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day2::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2018Day2PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "12")));

class TestYear2018Day2PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2018Day2PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2018/day2/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day2::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2018Day2PartTwo,
                         ::testing::Values(std::make_tuple("test_input1.txt",
                                                           "fgij")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day2

}  // namespace year2018
