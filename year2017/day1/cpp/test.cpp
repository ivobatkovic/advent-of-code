#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2017/day1/cpp/solutions.hpp"

using std::string;

namespace year2017 {

namespace day1 {

class TestYear2017Day1PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2017Day1PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2017/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOne, TestYear2017Day1PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", "9"),
                      std::make_tuple("test_input1.txt", "0")));

class TestYear2017Day1PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2017Day1PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2017/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartTwo, TestYear2017Day1PartTwo,
    ::testing::Values(std::make_tuple("test_input2.txt", "4"),
                      std::make_tuple("test_input3.txt", "6"),
                      std::make_tuple("test_input4.txt", "0")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day1

}  // namespace year2017
