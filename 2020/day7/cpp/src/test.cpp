#include <gtest/gtest.h>

#include <tuple>

#include "day7.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day7::solve_part1(day7::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest, PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", "4"),
                      std::make_tuple("test_input2.txt", "4")));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day7::solve_part2(day7::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartTwoTest, PartTwo,
    ::testing::Values(std::make_tuple("test_input0.txt", "32"),
                      std::make_tuple("test_input1.txt", "126")));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
