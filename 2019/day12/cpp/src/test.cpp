#include <gtest/gtest.h>

#include <tuple>

#include "2019/day12/cpp/include/gravity.hpp"

using std::string;
using std::vector;
using ::testing::TestWithParam;

typedef std::tuple<string, int, vector<vector<int>>, vector<vector<int>>> input;

class GravityTestUpdate : public TestWithParam<input> {};
class GravityTestEnergy : public TestWithParam<std::tuple<string, int, int>> {};

TEST_P(GravityTestUpdate, updateTestPos) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto nSteps = std::get<1>(param);
  auto expectedPos = std::get<2>(param);

  Gravity grav = Gravity(file_name);
  grav.update(nSteps);

  EXPECT_EQ(expectedPos, grav.m_pos);
}

TEST_P(GravityTestUpdate, updateTestVel) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto nSteps = std::get<1>(param);
  auto expectedVel = std::get<3>(param);

  Gravity grav = Gravity(file_name);
  grav.update(nSteps);

  EXPECT_EQ(expectedVel, grav.m_vel);
}

INSTANTIATE_TEST_SUITE_P(
    updateTests, GravityTestUpdate,
    ::testing::Values(
        std::make_tuple("test_input0.txt", 10,
                        vector<vector<int>>(
                            {{2, 1, -3}, {1, -8, 0}, {3, -6, 1}, {2, 0, 4}}),
                        vector<vector<int>>({{-3, -2, 1},
                                             {-1, 1, 3},
                                             {3, 2, -3},
                                             {1, -1, -1}})),
        std::make_tuple(
            "test_input1.txt", 100,
            vector<vector<int>>(
                {{8, -12, -9}, {13, 16, -3}, {-29, -11, -1}, {16, -13, 23}}),
            vector<vector<int>>(
                {{-7, 3, 0}, {3, -11, -5}, {-3, 7, 4}, {7, 1, 1}}))));

TEST_P(GravityTestEnergy, energyTest) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto nSteps = std::get<1>(param);
  auto expectedEnergy = std::get<2>(param);

  Gravity grav = Gravity(file_name);
  grav.update(nSteps);

  EXPECT_EQ(expectedEnergy, grav.energy());
}

INSTANTIATE_TEST_SUITE_P(
    energyTests, GravityTestEnergy,
    ::testing::Values(std::make_tuple("test_input0.txt", 10, 179),
                      std::make_tuple("test_input1.txt", 100, 1940)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
