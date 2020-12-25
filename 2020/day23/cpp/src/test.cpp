#include <gtest/gtest.h>

#include <tuple>

#include "day23.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int, int>> {
};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto n_rounds = std::get<1>(param);
  auto output = std::get<2>(param);
  EXPECT_EQ(output, day23::solve_part1(day23::read_input(file_name), n_rounds));
}

INSTANTIATE_TEST_SUITE_P(
    PartOneTest, PartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 10, 92658374),
                      std::make_tuple("test_input0.txt", 100, 67384529)));

class PartTwo : public ::testing::TestWithParam<std::tuple<string, size_t>> {};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day23::solve_part2(day23::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwoTest, PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           149245887792)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
