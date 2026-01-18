#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2018/day5/cpp/solutions.hpp"

using std::string;

namespace year2018 {

namespace day5 {

class TestYear2018Day5PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2018Day5PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2018/day5/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day5::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2018Day5PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "10")));

class TestYear2018Day5PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2018Day5PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2018/day5/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day5::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2018Day5PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "4")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day5

}  // namespace year2018
