#include <gtest/gtest.h>

#include <tuple>

#include "orbit.hpp"

using std::string;
using std::vector;

typedef std::tuple<string, int> input;

class OrbitTestPartOne : public ::testing::TestWithParam<input> {};
class OrbitTestPartTwo : public ::testing::TestWithParam<input> {};

TEST_P(OrbitTestPartOne, testOrbit) {
  // Get parameters
  auto param = GetParam();

  string file_name = std::get<0>(param);
  auto output = std::get<1>(param);

  Orbit orbit = Orbit(string(SOURCE_DIR) + "/data/" + file_name);
  EXPECT_EQ(output, orbit.get_number_of_orbits());
}

TEST_P(OrbitTestPartTwo, testOrbitals) {
  // Get parameters
  auto param = GetParam();
  string file_name = std::get<0>(param);
  auto output = std::get<1>(param);

  Orbit orbit = Orbit(string(SOURCE_DIR) + "/data/" + file_name);

  EXPECT_EQ(output, orbit.get_orbitals("YOU", "SAN"));
}

INSTANTIATE_TEST_SUITE_P(testOrbit, OrbitTestPartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           42)));

INSTANTIATE_TEST_SUITE_P(testOrbitals, OrbitTestPartTwo,
                         ::testing::Values(std::make_tuple("test_input1.txt",
                                                           4)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
