#include <gtest/gtest.h>

#include <tuple>

#include "2020/day15/cpp/include/day15.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day15::solve_part1(day15::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest, PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 436),
                      std::make_tuple("test_input1.txt", 1),
                      std::make_tuple("test_input2.txt", 10),
                      std::make_tuple("test_input3.txt", 27),
                      std::make_tuple("test_input4.txt", 78),
                      std::make_tuple("test_input5.txt", 438),
                      std::make_tuple("test_input6.txt", 1836)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
