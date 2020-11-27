#include <gtest/gtest.h>
#include "formula.hpp"
#include <tuple>

using std::vector;
using std::string;

typedef std::tuple<string, int> input;

class FormulaComputeTest : public ::testing::TestWithParam<input> {};
class FormulaComputeFuelTest : public ::testing::TestWithParam<input> {};

TEST_P(FormulaComputeTest, computeTest)
{
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Formula formula = Formula(file_name);

  EXPECT_EQ(expectedOutput, formula.compute("ORE", 1));
}

INSTANTIATE_TEST_SUITE_P(
    computeTests,
    FormulaComputeTest,
    ::testing::Values(
        std::make_tuple("test_input0.txt", 31),
        std::make_tuple("test_input1.txt", 165),
        std::make_tuple("test_input2.txt", 13312),
        std::make_tuple("test_input3.txt", 180697),
        std::make_tuple("test_input4.txt", 2210736)));

TEST_P(FormulaComputeFuelTest, computeFuelTest)
{
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Formula formula = Formula(file_name);

  EXPECT_EQ(expectedOutput, formula.compute_fuel());
}

INSTANTIATE_TEST_SUITE_P(
    computeFuelTests,
    FormulaComputeFuelTest,
    ::testing::Values(
        std::make_tuple("test_input2.txt", 82892753),
        std::make_tuple("test_input3.txt", 5586022),
        std::make_tuple("test_input4.txt", 460664)));

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
