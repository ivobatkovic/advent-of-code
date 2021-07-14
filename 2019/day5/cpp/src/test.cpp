#include <gtest/gtest.h>

#include <tuple>

#include "2019/day5/cpp/include/intcode.hpp"

using std::string;
using std::vector;

typedef std::tuple<string, int, int> input;

class IntcodeTest : public ::testing::TestWithParam<input> {};

TEST_P(IntcodeTest, testIntcode) {
  // Get parameters
  auto param = GetParam();

  auto file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);

  Intcode intcode(file_name, {std::get<1>(param)}, false, false);
  auto output = intcode();

  auto desired_output = std::get<2>(param);
  EXPECT_EQ(desired_output, std::get<1>(output));
}

INSTANTIATE_TEST_SUITE_P(
    testIntcode, IntcodeTest,
    ::testing::Values(std::make_tuple("test_input0.txt", 1, 0),
                      std::make_tuple("test_input0.txt", 8, 1),
                      std::make_tuple("test_input1.txt", 1, 1),
                      std::make_tuple("test_input1.txt", 8, 0),
                      std::make_tuple("test_input1.txt", 9, 0),
                      std::make_tuple("test_input2.txt", 1, 0),
                      std::make_tuple("test_input2.txt", 8, 1),
                      std::make_tuple("test_input2.txt", 9, 0),
                      std::make_tuple("test_input3.txt", 1, 1),
                      std::make_tuple("test_input3.txt", 8, 0),
                      std::make_tuple("test_input3.txt", 9, 0),
                      std::make_tuple("test_input4.txt", 0, 0),
                      std::make_tuple("test_input4.txt", -9, 1),
                      std::make_tuple("test_input5.txt", 0, 0),
                      std::make_tuple("test_input5.txt", -9, 1),
                      std::make_tuple("test_input6.txt", -9, 999),
                      std::make_tuple("test_input6.txt", 9, 1001)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
