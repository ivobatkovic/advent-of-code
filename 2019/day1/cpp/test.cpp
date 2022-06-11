#include <gtest/gtest.h>

#include <tuple>

#include "cpp_utils.hpp"
#include "solutions.hpp"

using std::string;

class TestDay1PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestDay1PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "2019/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestDay1PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "0")));

class TestDay1PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestDay1PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "2019/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestDay1PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "0")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
