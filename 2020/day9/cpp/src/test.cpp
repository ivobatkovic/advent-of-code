#include <gtest/gtest.h>

#include <tuple>

#include "day9.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int, int>> {
};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto preamble = std::get<1>(param);
  auto output = std::get<2>(param);
  EXPECT_EQ(output, day9::solve_part1(day9::read_input(file_name), preamble));
}

INSTANTIATE_TEST_SUITE_P(PartOneTest, PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt", 5,
                                                           127)));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, int, int>> {
};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto preamble = std::get<1>(param);
  auto output = std::get<2>(param);
  EXPECT_EQ(output, day9::solve_part2(day9::read_input(file_name), preamble));
}

INSTANTIATE_TEST_SUITE_P(PartTwoTest, PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt", 5,
                                                           62)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
