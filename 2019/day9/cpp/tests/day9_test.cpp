#include <gtest/gtest.h>
#include "intcode.hpp"
#include <tuple>

using std::vector;
using std::string;
using ::testing::TestWithParam;

typedef std::tuple<std::string, int64_t> input;
class IntcodeTestPartOne : public TestWithParam<input> {};
class IntcodeTestPartTwo : public TestWithParam<string> {};

TEST_P(IntcodeTestPartOne, testLargeNumbers)
{
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR)+ "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);

  Intcode intcode = Intcode(file_name,{},true,false);

  // Run until terminated
  bool terminated(false);
  int64_t output_intcode;
  while(!terminated) {
    auto output_ = intcode();
    terminated = std::get<0>(output_);
    output_intcode = std::get<1>(output_);
  }

  EXPECT_EQ(output, output_intcode);
}

INSTANTIATE_TEST_SUITE_P(
    testLargeNumbers,
    IntcodeTestPartOne,
    ::testing::Values(
        std::make_tuple("test_input1.csv", 1219070632396864),
        std::make_tuple("test_input2.csv", 1125899906842624)));

TEST_P(IntcodeTestPartTwo, testOutput)
{
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + param;

  // Access the stored program
  Intcode intcode = Intcode(file_name, {}, false, false);  
  auto program = intcode.m_program;

  
  // Map for output
  vector<int64_t> digits;

  // Run until termination
  bool terminated(false);
  while (!terminated)
  {
    auto output_ = intcode();
    terminated = std::get<0>(output_);
    if (!terminated) {
      digits.push_back(std::get<1>(output_));
    }
  }

  EXPECT_EQ(program, digits);
}

INSTANTIATE_TEST_SUITE_P(
    testOutput,
    IntcodeTestPartTwo,
    ::testing::Values("test_input0.csv"));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
