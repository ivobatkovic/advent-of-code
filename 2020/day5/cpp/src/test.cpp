#include <gtest/gtest.h>

#include <tuple>

#include "2020/day5/cpp/include/day5.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day5::solve_part1(day5::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest, PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", "357"),
                      std::make_tuple("test_input1.txt", "567"),
                      std::make_tuple("test_input2.txt", "119"),
                      std::make_tuple("test_input3.txt", "820")));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
