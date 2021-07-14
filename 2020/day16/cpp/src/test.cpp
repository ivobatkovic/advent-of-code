#include <gtest/gtest.h>

#include <tuple>

#include "2020/day16/cpp/include/day16.hpp"

using std::string;

class PartOne : public ::testing::TestWithParam<std::tuple<string, int>> {};

TEST_P(PartOne, PartOneTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, day16::solve_part1(day16::read_input(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOneTest, PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           71)));

class PartTwo : public ::testing::TestWithParam<
                    std::tuple<string, std::unordered_map<std::string, int>>> {
};

TEST_P(PartTwo, PartTwoTest) {
  auto param = GetParam();
  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto input_ = day16::read_input(file_name);
  auto valid_tickets = day16::get_valid_tickets(input_);
  auto field_index = day16::match_field_to_index(valid_tickets, input_.first);
  auto output = std::get<1>(param);
  EXPECT_EQ(output, field_index);
}

INSTANTIATE_TEST_SUITE_P(PartTwoTest, PartTwo,
                         ::testing::Values(std::make_tuple(
                             "test_input0.txt",
                             std::unordered_map<std::string, int>(
                                 {{"row", 0}, {"class", 1}, {"seat", 2}}))));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
