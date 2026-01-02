#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2016/day2/cpp/solutions.hpp"

using std::string;

namespace year2016 {

namespace day2 {

class TestYear2016Day2PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2016Day2PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2016/day2/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day2::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2016Day2PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "1985")));

class TestYear2016Day2PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2016Day2PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2016/day2/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day2::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2016Day2PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "5DB3")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day2

}  // namespace year2016
