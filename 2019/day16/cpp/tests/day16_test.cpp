#include <gtest/gtest.h>

#include <tuple>

#include "fft.hpp"

using std::string;
using std::vector;

typedef std::tuple<string, string, int> inputOne;
typedef std::tuple<string, string> inputTwo;

class FFTTest : public ::testing::TestWithParam<inputOne> {};
class FFTDecode : public ::testing::TestWithParam<inputTwo> {};

TEST_P(FFTTest, updateTest) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  int n_updates = std::get<2>(param);
  FFT fft = FFT(file_name);

  EXPECT_EQ(expectedOutput, fft.part_one(n_updates));
}

INSTANTIATE_TEST_SUITE_P(
    partOne, FFTTest,
    ::testing::Values(std::make_tuple("test_input0.txt", "48226158", 1),
                      std::make_tuple("test_input0.txt", "34040438", 2),
                      std::make_tuple("test_input0.txt", "03415518", 3),
                      std::make_tuple("test_input0.txt", "01029498", 4),
                      std::make_tuple("test_input1.txt", "24176176", 100),
                      std::make_tuple("test_input2.txt", "73745418", 100),
                      std::make_tuple("test_input3.txt", "52432133", 100)));

TEST_P(FFTDecode, decodeTest) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  FFT fft = FFT(file_name);

  EXPECT_EQ(expectedOutput, fft.part_two());
}

INSTANTIATE_TEST_SUITE_P(
    partTwo, FFTDecode,
    ::testing::Values(std::make_tuple("test_input4.txt", "84462026"),
                      std::make_tuple("test_input5.txt", "78725270"),
                      std::make_tuple("test_input6.txt", "53553731")));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
