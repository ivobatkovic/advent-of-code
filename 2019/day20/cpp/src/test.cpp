#include <gtest/gtest.h>

#include <tuple>

#include "2019/day20/cpp/include/donut.hpp"

using std::string;
using std::vector;
using ::testing::TestWithParam;

class DonutTestOne : public TestWithParam<std::tuple<string, int> > {};
class DonutTestTwo : public TestWithParam<std::tuple<string, int> > {};

TEST_P(DonutTestOne, partOne) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Donut donut(file_name);

  EXPECT_EQ(expectedOutput, donut.shortest_path());
}

INSTANTIATE_TEST_SUITE_P(
    partOne, DonutTestOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 23),
                      std::make_tuple("test_input1.txt", 58)));

TEST_P(DonutTestTwo, partTwo) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Donut donut(file_name);

  EXPECT_EQ(expectedOutput, donut.shortest_path(true));
}

INSTANTIATE_TEST_SUITE_P(
    partTwo, DonutTestTwo,
    ::testing::Values(std::make_tuple("test_input0.txt", 26),
                      std::make_tuple("test_input2.txt", 396)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
