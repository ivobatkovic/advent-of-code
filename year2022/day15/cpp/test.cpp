#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day15/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day15 {

class TestYear2022Day15PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day15PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2022/day15/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day15::solve_part1(utils::read_file_to_string(file_name), 10));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2022Day15PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "26")));

class TestYear2022Day15PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day15PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2022/day15/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day15::solve_part2(utils::read_file_to_string(file_name), 20));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2022Day15PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "56000011")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day15

}  // namespace year2022
