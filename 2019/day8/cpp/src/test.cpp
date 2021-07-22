#include <gtest/gtest.h>

#include <tuple>

#include "2019/day8/cpp/include/spaceimage.hpp"

using std::string;
using std::vector;

typedef std::tuple<string, string> input;
class SpaceImageTest : public ::testing::TestWithParam<input> {};

TEST_P(SpaceImageTest, testImage) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto output = std::get<1>(param);

  SpaceImage image(file_name, 2, 2);
  EXPECT_EQ(output, image.reconstruct_image());
}

INSTANTIATE_TEST_SUITE_P(testImage, SpaceImageTest,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "0110")));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
