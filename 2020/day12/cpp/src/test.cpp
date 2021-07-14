#include <gtest/gtest.h>

#include <tuple>

#include "2020/day12/cpp/include/day12.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day12::solve_part1(day12::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOneTest, PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           25)));

class ParTTwo : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(ParTTwo, ParTTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day12::solve_part2(day12::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(ParTTwoTest, ParTTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           286)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
