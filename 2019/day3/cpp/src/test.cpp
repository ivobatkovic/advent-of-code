#include <gtest/gtest.h>

#include <tuple>

#include "2019/day3/cpp/include/wires.hpp"

using std::vector;

class Test : public ::testing::TestWithParam<std::tuple<std::string, int>> {};
class WiresPartOne : public Test {};
class WiresPartTwo : public Test {};

TEST_P(WiresPartOne, partOne) {
  // Get parameters
  auto param = GetParam();
  std::string input = std::string(SOURCE_DIR) + std::get<0>(param);
  Wires wire(input);

  wire.solve();

  // Compare output with desired output
  EXPECT_EQ(wire.m_distance, std::get<1>(param));
}

TEST_P(WiresPartTwo, partTwo) {
  // Get parameters
  auto param = GetParam();
  std::string input = std::string(SOURCE_DIR) + std::get<0>(param);
  Wires wire(input);

  wire.solve();

  // Compare output with desired output
  EXPECT_EQ(wire.m_steps, std::get<1>(param));
}

INSTANTIATE_TEST_SUITE_P(
    partOne, WiresPartOne,
    ::testing::Values(std::make_tuple("/data/test_input0.txt", 159),
                      std::make_tuple("/data/test_input1.txt", 135)));

INSTANTIATE_TEST_SUITE_P(
    partTwo, WiresPartTwo,
    ::testing::Values(std::make_tuple("/data/test_input2.txt", 610),
                      std::make_tuple("/data/test_input3.txt", 410)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
