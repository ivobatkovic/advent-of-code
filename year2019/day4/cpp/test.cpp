#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2019/day4/cpp/solutions.hpp"

using std::string;

namespace year2019 {

namespace day4 {

class TestYear2019Day4PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2019Day4PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2019/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2019Day4PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "1")));

class TestYear2019Day4PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2019Day4PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2019/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2019Day4PartTwo,
                         ::testing::Values(std::make_tuple("test_input1.txt",
                                                           "2")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day4

}  // namespace year2019
