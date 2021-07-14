#include <gtest/gtest.h>

#include <tuple>

#include "2019/day18/cpp/include/maze.hpp"

using std::vector;

class MazeTest : public ::testing::TestWithParam<std::tuple<std::string, int>> {
};
class MazeMultiTest
    : public ::testing::TestWithParam<std::tuple<std::string, int>> {};

TEST_P(MazeTest, partOne) {
  // Get parameters
  auto param = GetParam();
  std::string file_name =
      std::string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Maze maze(file_name);

  EXPECT_EQ(expectedOutput, maze.compute_shortest_path());
}

INSTANTIATE_TEST_SUITE_P(
    partOne, MazeTest,
    ::testing::Values(std::make_tuple("test_input0.txt", 8),
                      std::make_tuple("test_input1.txt", 86),
                      std::make_tuple("test_input2.txt", 132),
                      std::make_tuple("test_input3.txt", 136),
                      std::make_tuple("test_input4.txt", 81)));

TEST_P(MazeMultiTest, partTwo) {
  // Get parameters
  auto param = GetParam();
  std::string file_name =
      std::string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Maze maze(file_name, true);

  EXPECT_EQ(expectedOutput, maze.compute_shortest_path());
}

INSTANTIATE_TEST_SUITE_P(
    partTwo, MazeMultiTest,
    ::testing::Values(std::make_tuple("test_input5.txt", 8),
                      std::make_tuple("test_input6.txt", 24),
                      std::make_tuple("test_input7.txt", 32),
                      std::make_tuple("test_input8.txt", 72)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
