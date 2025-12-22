#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2016/day1/cpp/solutions.hpp"

using std::string;

namespace year2016 {

namespace day1 {

class TestYear2016Day1PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2016Day1PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2016/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2016Day1PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "12")));

class TestYear2016Day1PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2016Day1PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2016/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2016Day1PartTwo,
                         ::testing::Values(std::make_tuple("test_input1.txt",
                                                           "4")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day1

}  // namespace year2016
