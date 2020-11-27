#include <gtest/gtest.h>
#include "digits.hpp"
#include <tuple>
#include <iostream>

using std::vector;
using std::string;


typedef std::tuple<string, bool> testInput;

class DigitsPartOne : public ::testing::TestWithParam<testInput> {};
class DigitsPartTwo : public ::testing::TestWithParam<testInput> {};

TEST_P(DigitsPartOne, partOne)
{
  // Get parameters
  auto param = GetParam();

  // Check if input is monotonic
  string input = std::get<0>(param);
  string monotonic_digit = Digits::make_monotonic(input);
  bool monotonic = (monotonic_digit == input) ? true : false;

  // Check if input satisfies montonicity and double digits
  bool is_double_digit = Digits::double_digit(monotonic_digit);
  bool double_digits = (monotonic & is_double_digit) ? true : false;

  // Compare output with desired output
  EXPECT_EQ(std::get<1>(param), double_digits);
}

TEST_P(DigitsPartTwo, partTwo)
{
  // Get parameters
  auto param = GetParam();

  // Check if input is monotonic
  string input = std::get<0>(param);
  string monotonic_digit = Digits::make_monotonic(input);
  bool monotonic = (monotonic_digit == input) ? true : false;

  // Check if input satisfies montonicity and double digits
  bool is_double_digit = Digits::double_digit_no_adjacent(monotonic_digit);
  bool double_digits = (monotonic & is_double_digit) ? true : false;

  // Compare output with desired output
  EXPECT_EQ(std::get<1>(param), double_digits);
}

INSTANTIATE_TEST_SUITE_P(
    partOne,
    DigitsPartOne,
    ::testing::Values(
        std::make_tuple("111111", true),
        std::make_tuple("223450", false),
        std::make_tuple("123789", false)));

INSTANTIATE_TEST_SUITE_P(
    partTwo,
    DigitsPartTwo,
    ::testing::Values(
        std::make_tuple("112233", true),
        std::make_tuple("123444", false),
        std::make_tuple("111122", true)));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
