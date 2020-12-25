#include <gtest/gtest.h>

#include <tuple>

#include "day24.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day24::solve_part1(day24::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOneTest, PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           10)));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day24::solve_part2(day24::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwoTest, PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           2208)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
