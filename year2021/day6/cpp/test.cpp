#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2021/day6/cpp/solutions.hpp"

using std::string;

namespace year2021 {

namespace day6 {

class TestYear2021Day6PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2021Day6PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2021/day6/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day6::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2021Day6PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "5934")));

class TestYear2021Day6PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2021Day6PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2021/day6/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day6::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2021Day6PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "26984457539")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day6

}  // namespace year2021
