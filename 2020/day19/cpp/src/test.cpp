#include <gtest/gtest.h>

#include <tuple>

#include "2020/day19/cpp/include/day19.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day19::solve_part1(day19::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest, PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 2),
                      std::make_tuple("test_input1.txt", 2),
                      std::make_tuple("test_input2.txt", 3)));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day19::solve_part2(day19::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwoTest, PartTwo,
                         ::testing::Values(std::make_tuple("test_input2.txt",
                                                           12)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
