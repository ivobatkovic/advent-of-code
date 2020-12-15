#include <gtest/gtest.h>

#include <tuple>

#include "amplifier.hpp"

using std::string;
using std::vector;

typedef std::tuple<string, int> input;

class AmplifierTestPartOne : public ::testing::TestWithParam<input> {};
class AmplifierTestPartTwo : public ::testing::TestWithParam<input> {};

TEST_P(AmplifierTestPartOne, testAmplifierPartOne) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);

  EXPECT_EQ(output, Amplifier::get_maximum_thrust(file_name));
}

INSTANTIATE_TEST_SUITE_P(
    testAmplifierPartOne, AmplifierTestPartOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 43210),
                      std::make_tuple("test_input1.txt", 54321),
                      std::make_tuple("test_input2.txt", 65210)));

TEST_P(AmplifierTestPartTwo, testAmplifierPartTwo) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);

  EXPECT_EQ(output, Amplifier::feedback_thrust(file_name));
}

INSTANTIATE_TEST_SUITE_P(
    testAmplifierPartTwo, AmplifierTestPartTwo,
    ::testing::Values(std::make_tuple("test_input3.txt", 139629729),
                      std::make_tuple("test_input4.txt", 18216)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
