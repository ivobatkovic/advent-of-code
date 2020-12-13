#include <gtest/gtest.h>
#include "day13.hpp"
#include <tuple>

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int64_t>>
{
};

TEST_P(PartOne, PartOneTest)
{ 
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day13::solve_part1(day13::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest,
    PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 295)));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, int64_t>>
{
};

TEST_P(PartTwo, PartTwoTest)
{ 
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day13::solve_part2(day13::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartTwoTest,
    PartTwo,
    ::testing::Values(std::make_tuple("test_input0.txt", 1068781),
                      std::make_tuple("test_input1.txt", 3417),
                      std::make_tuple("test_input2.txt", 754018),
                      std::make_tuple("test_input3.txt", 779210),
                      std::make_tuple("test_input4.txt", 1261476),
                      std::make_tuple("test_input5.txt", 1202161486)));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
