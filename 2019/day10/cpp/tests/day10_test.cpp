#include <gtest/gtest.h>

#include <tuple>

#include "monitorstation.hpp"

using std::vector;

using std::string;
using ::testing::TestWithParam;

typedef std::tuple<string, int, int> input;

class MonitorStationTest : public TestWithParam<input> {};
class MonitorStationTest2 : public TestWithParam<input> {};

TEST_P(MonitorStationTest, testMaxAsteroids) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);

  MonitorStation station(file_name);
  auto output = station.compute_vision(station.m_input);

  auto n_asteroids = std::get<1>(param);

  EXPECT_EQ(n_asteroids, std::get<0>(output));
}

TEST_P(MonitorStationTest2, testMaxAsteroids2) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto ith_asteroid = std::get<1>(param);
  auto expectedOutput = std::get<2>(param);

  MonitorStation stn(file_name);
  auto output = stn.compute_vision(stn.m_input);
  int outputValue = stn.blast(stn.m_input, std::get<1>(output), ith_asteroid);

  EXPECT_EQ(expectedOutput, outputValue);
}

INSTANTIATE_TEST_SUITE_P(
    testMaxAsteroids, MonitorStationTest,
    ::testing::Values(std::make_tuple("test_input0.txt", 33, 3),
                      std::make_tuple("test_input1.txt", 35, 3),
                      std::make_tuple("test_input2.txt", 41, 3),
                      std::make_tuple("test_input3.txt", 210, 3)));

INSTANTIATE_TEST_SUITE_P(
    testMaxAsteroids2, MonitorStationTest2,
    ::testing::Values(std::make_tuple("test_input3.txt", 1, 11 * 100 + 12),
                      std::make_tuple("test_input3.txt", 2, 12 * 100 + 1),
                      std::make_tuple("test_input3.txt", 3, 12 * 100 + 2),
                      std::make_tuple("test_input3.txt", 10, 12 * 100 + 8),
                      std::make_tuple("test_input3.txt", 20, 16 * 100 + 0),
                      std::make_tuple("test_input3.txt", 50, 16 * 100 + 9),
                      std::make_tuple("test_input3.txt", 100, 10 * 100 + 16),
                      std::make_tuple("test_input3.txt", 199, 9 * 100 + 6),
                      std::make_tuple("test_input3.txt", 200, 8 * 100 + 2),
                      std::make_tuple("test_input3.txt", 201, 10 * 100 + 9),
                      std::make_tuple("test_input3.txt", 299, 11 * 100 + 1)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
