#include <gtest/gtest.h>
#include "intcode.hpp"
#include <tuple>

using std::vector;
using std::string;

typedef std::tuple<string, int, int> input;

class IntcodeTest : public ::testing::TestWithParam<input> {};


TEST_P(IntcodeTest, testIntcode)
{
  // Get parameters
  auto param = GetParam();

  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);

  Intcode intcode(file_name, { std::get<1>(param) }, false, false);
  auto output = intcode();

  auto desired_output = std::get<2>(param);
  EXPECT_EQ(desired_output, std::get<1>(output));
}

INSTANTIATE_TEST_SUITE_P(
    testIntcode,
    IntcodeTest,
    ::testing::Values(std::make_tuple("test_input0.csv", 1, 0),
                      std::make_tuple("test_input0.csv", 8, 1),
                      std::make_tuple("test_input1.csv", 1, 1),
                      std::make_tuple("test_input1.csv", 8, 0),
                      std::make_tuple("test_input1.csv", 9, 0),
                      std::make_tuple("test_input2.csv", 1, 0),
                      std::make_tuple("test_input2.csv", 8, 1),
                      std::make_tuple("test_input2.csv", 9, 0),
                      std::make_tuple("test_input3.csv", 1, 1),
                      std::make_tuple("test_input3.csv", 8, 0),
                      std::make_tuple("test_input3.csv", 9, 0),
                      std::make_tuple("test_input4.csv", 0, 0),
                      std::make_tuple("test_input4.csv", -9, 1),
                      std::make_tuple("test_input5.csv", 0, 0),
                      std::make_tuple("test_input5.csv", -9, 1),
                      std::make_tuple("test_input6.csv", -9, 999),
                      std::make_tuple("test_input6.csv", 9, 1001)
                      ));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
