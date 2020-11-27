#include <gtest/gtest.h>
#include "amplifier.hpp"
#include <tuple>

using std::vector;
using std::string;

typedef std::tuple<string, int> input;

class AmplifierTestPartOne : public ::testing::TestWithParam<input> {};
class AmplifierTestPartTwo : public ::testing::TestWithParam<input> {};

TEST_P(AmplifierTestPartOne, testAmplifierPartOne)
{
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);

  EXPECT_EQ(output, Amplifier::get_maximum_thrust(file_name));
}

INSTANTIATE_TEST_SUITE_P(
    testAmplifierPartOne,
    AmplifierTestPartOne,
    ::testing::Values(std::make_tuple("test_input0.csv", 43210),
                      std::make_tuple("test_input1.csv", 54321),
                      std::make_tuple("test_input2.csv", 65210)));

TEST_P(AmplifierTestPartTwo, testAmplifierPartTwo)
{
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);

  EXPECT_EQ(output, Amplifier::feedback_thrust(file_name));
}

INSTANTIATE_TEST_SUITE_P(
    testAmplifierPartTwo,
    AmplifierTestPartTwo,
    ::testing::Values(std::make_tuple("test_input3.csv", 139629729),
                      std::make_tuple("test_input4.csv", 18216)));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
