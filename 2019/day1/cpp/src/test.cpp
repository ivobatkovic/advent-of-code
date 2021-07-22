#include <gtest/gtest.h>

#include <tuple>

#include "2019/day1/cpp/include/fuel_counter.hpp"

class Test : public ::testing::TestWithParam<std::tuple<int, int>> {
 protected:
  FuelCounter m_counter = FuelCounter();
};

class TestFuelCounter : public Test {};
class TestFuelCounterExtended : public Test {};

TEST_P(TestFuelCounter, partOne) {
  auto param = GetParam();
  auto res = std::get<0>(param);
  auto val = std::get<1>(param);
  EXPECT_EQ(res, m_counter.fuel_counter(val));
}

TEST_P(TestFuelCounterExtended, partTwo) {
  auto param = GetParam();
  auto res = std::get<0>(param);
  auto val = std::get<1>(param);
  m_counter.m_masses.push_back(val);
  EXPECT_EQ(res, m_counter.fuel_counter_extended(m_counter.m_masses));
}

INSTANTIATE_TEST_SUITE_P(partOne, TestFuelCounter,
                         ::testing::Values(std::make_tuple(2, 12),
                                           std::make_tuple(2, 14),
                                           std::make_tuple(654, 1969),
                                           std::make_tuple(33583, 100756)));

INSTANTIATE_TEST_SUITE_P(partTwo, TestFuelCounterExtended,
                         ::testing::Values(std::make_tuple(2, 14),
                                           std::make_tuple(966, 1969),
                                           std::make_tuple(50346, 100756)));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
