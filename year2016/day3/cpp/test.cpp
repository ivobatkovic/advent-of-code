#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2016/day3/cpp/solutions.hpp"

using std::string;

namespace year2016 {

namespace day3 {

class TestYear2016Day3PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2016Day3PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2016/day3/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day3::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2016Day3PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "0")));

class TestYear2016Day3PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2016Day3PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2016/day3/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day3::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2016Day3PartTwo,
                         ::testing::Values(std::make_tuple("test_input1.txt",
                                                           "6")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day3

}  // namespace year2016
