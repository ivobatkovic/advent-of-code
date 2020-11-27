#include <gtest/gtest.h>
#include "intcode.hpp"
#include<tuple>

using std::vector;

typedef std::tuple<vector<int>, vector<int>> input;

class Test : public ::testing::TestWithParam<input>
{
  protected:
    Intcode intcode = Intcode(false);
};

class IntcodeOperations : public Test {};

TEST_P(IntcodeOperations, partOne)
{ 
  // Get parameters
  auto param = GetParam();
  
  // Load in the program
  this->intcode.m_memory = std::get<0>(param);

  // Call intcode
  intcode();
  
  // Compare output with desired output
  EXPECT_EQ(this->intcode.m_memory,std::get<1>(param));
}


INSTANTIATE_TEST_SUITE_P(
    partOne,
    IntcodeOperations,
    ::testing::Values(
        std::make_tuple(vector<int>{1, 0, 0, 0, 99}, 
                        vector<int>{2, 0, 0, 0, 99}),
        std::make_tuple(vector<int>{2, 3, 0, 3, 99}, 
                        vector<int>{2, 3, 0, 6, 99}),
        std::make_tuple(vector<int>{2, 4, 4, 5, 99, 0},
                        vector<int>{2, 4, 4, 5, 99, 9801}),
        std::make_tuple(vector<int>{1, 1, 1, 4, 99, 5, 6, 0, 99},
                        vector<int>{30, 1, 1, 4, 2, 5, 6, 0, 99})));


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
