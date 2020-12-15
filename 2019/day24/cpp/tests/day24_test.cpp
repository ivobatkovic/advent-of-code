#include <gtest/gtest.h>

#include <tuple>

#include "planet.hpp"

using std::string;
using std::vector;
using ::testing::TestWithParam;
typedef std::tuple<std::string, int, std::vector<std::string>> input;

class PlanetTestOne : public TestWithParam<input> {};
class PlanetTestTwo : public TestWithParam<std::tuple<string, int>> {};
class PlanetTestThree : public TestWithParam<std::tuple<string, int, int>> {};

TEST_P(PlanetTestOne, update) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<2>(param);

  Planet planet(file_name);

  for (int i = 0; i < std::get<1>(param); i++) {
    planet.update();
  }

  EXPECT_EQ(expectedOutput, planet.m_grid[0].data);
}

TEST_P(PlanetTestTwo, partOne) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);

  Planet planet(file_name);

  EXPECT_EQ(expectedOutput, planet.part_one());
}

TEST_P(PlanetTestThree, partTwo) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto nSteps = std::get<1>(param);
  auto expectedOutput = std::get<2>(param);

  Planet planet(file_name, true);

  EXPECT_EQ(expectedOutput, planet.part_two(nSteps));
}

INSTANTIATE_TEST_SUITE_P(
    update, PlanetTestOne,
    ::testing::Values(
        std::make_tuple("test_input0.txt", 1,
                        std::vector<string>({"#..#.", "####.", "###.#", "##.##",
                                             ".##.."})),
        std::make_tuple("test_input0.txt", 2,
                        std::vector<string>({"#####", "....#", "....#", "...#.",
                                             "#.###"})),
        std::make_tuple("test_input0.txt", 3,
                        std::vector<string>({"#....", "####.", "...##", "#.##.",
                                             ".##.#"})),
        std::make_tuple("test_input0.txt", 4,
                        std::vector<string>({"####.", "....#", "##..#", ".....",
                                             "##..."}))));

INSTANTIATE_TEST_SUITE_P(partOne, PlanetTestTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           2129920)));

INSTANTIATE_TEST_SUITE_P(partTwo, PlanetTestThree,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           10, 99)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
