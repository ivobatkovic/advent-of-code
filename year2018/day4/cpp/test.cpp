#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2018/day4/cpp/solutions.hpp"

using std::string;

namespace year2018 {

namespace day4 {

class TestYear2018Day4PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2018Day4PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2018/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2018Day4PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "240")));

class TestYear2018Day4PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2018Day4PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2018/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2018Day4PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "4455")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day4

}  // namespace year2018
