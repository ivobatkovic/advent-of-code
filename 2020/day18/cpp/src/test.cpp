#include <gtest/gtest.h>

#include <tuple>

#include "2020/day18/cpp/include/day18.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day18::solve_part1(day18::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest, PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 71),
                      std::make_tuple("test_input1.txt", 51),
                      std::make_tuple("test_input2.txt", 26),
                      std::make_tuple("test_input3.txt", 437),
                      std::make_tuple("test_input4.txt", 12240),
                      std::make_tuple("test_input5.txt", 13632)));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day18::solve_part2(day18::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartTwoTest, PartTwo,
    ::testing::Values(std::make_tuple("test_input0.txt", 231),
                      std::make_tuple("test_input1.txt", 51),
                      std::make_tuple("test_input2.txt", 46),
                      std::make_tuple("test_input3.txt", 1445),
                      std::make_tuple("test_input4.txt", 669060),
                      std::make_tuple("test_input5.txt", 23340)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
