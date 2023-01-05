#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day10/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day10 {

class TestYear2022Day10PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day10PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2022/day10/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day10::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2022Day10PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "13140")));

class TestYear2022Day10PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day10PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2022/day10/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day10::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2022Day10PartTwo,
                         ::testing::Values(std::make_tuple(
                             "test_input0.txt",
                             "\n##..##..##..##..##..##..##..##..##..##..\n"
                             "###...###...###...###...###...###...###.\n"
                             "####....####....####....####....####....\n"
                             "#####.....#####.....#####.....#####.....\n"
                             "######......######......######......####\n"
                             "#######.......#######.......#######.....")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day10

}  // namespace year2022
