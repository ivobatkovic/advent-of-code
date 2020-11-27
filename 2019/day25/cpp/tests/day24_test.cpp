#include <gtest/gtest.h>
#include "planet.hpp"
#include <tuple>

using std::vector;

class PlanetTestOne : public ::testing::TestWithParam<std::tuple<std::string, int,std::vector<std::string> > > {};
class PlanetTestTwo : public ::testing::TestWithParam<std::tuple<std::string, int> > {};
class PlanetTestThree : public ::testing::TestWithParam<std::tuple<std::string, int,int>>{};

TEST_P(PlanetTestOne, update)
{
  // Get parameters
  auto param = GetParam();
  std::string file_name = std::string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<2>(param);
  
  Planet planet(file_name);

  for (int i = 0; i < std::get<1>(param); i++) {
    planet.update();
  }

  EXPECT_EQ(expectedOutput, planet.grid[0].i);
}

TEST_P(PlanetTestTwo, partOne)
{
  // Get parameters
  auto param = GetParam();
  std::string file_name = std::string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);

  Planet planet(file_name);

  EXPECT_EQ(expectedOutput, planet.part_one());
}

TEST_P(PlanetTestThree, partTwo)
{
  // Get parameters
  auto param = GetParam();
  std::string file_name = std::string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto nSteps = std::get<1>(param);
  auto expectedOutput = std::get<2>(param);

  Planet planet(file_name,true);

  EXPECT_EQ(expectedOutput, planet.part_two(nSteps));
}

INSTANTIATE_TEST_SUITE_P(
    update,
    PlanetTestOne,
    ::testing::Values(std::make_tuple("test_input0.txt", 1, std::vector<std::string>({"#..#.", "####.", "###.#", "##.##", ".##.."})),
                      std::make_tuple("test_input0.txt", 2, std::vector<std::string>({"#####", "....#", "....#", "...#.", "#.###"})),
                      std::make_tuple("test_input0.txt", 3, std::vector<std::string>({"#....", "####.", "...##", "#.##.", ".##.#"})),
                      std::make_tuple("test_input0.txt", 4, std::vector<std::string>({"####.", "....#", "##..#", ".....", "##..."}))));

INSTANTIATE_TEST_SUITE_P(
    partOne,
    PlanetTestTwo,
    ::testing::Values(std::make_tuple("test_input0.txt", 2129920)));

INSTANTIATE_TEST_SUITE_P(
    partTwo,
    PlanetTestThree,
    ::testing::Values(std::make_tuple("test_input0.txt", 10, 99)));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
