#include <gtest/gtest.h>

#include <tuple>

#include "deck.hpp"

using std::string;
using std::vector;
typedef std::tuple<string, std::vector<int>> input;
class DeckTestOne : public ::testing::TestWithParam<input> {};

TEST_P(DeckTestOne, partOne) {
  // Get parameters
  auto param = GetParam();
  string file_name = string(SOURCE_DIR) + "/data/" + std::get<0>(param);
  auto expectedOutput = std::get<1>(param);
  Deck deck(file_name, 10);

  std::vector<int> output(10, 0);
  for (int i = 0; i < 10; i++) {
    output[(deck.m_a * i + deck.m_b) % 10] = i;
  }

  EXPECT_EQ(expectedOutput, output);
}

INSTANTIATE_TEST_SUITE_P(
    partOne, DeckTestOne,
    ::testing::Values(
        std::make_tuple("test_input0.txt",
                        std::vector<int>({0, 3, 6, 9, 2, 5, 8, 1, 4, 7})),
        std::make_tuple("test_input1.txt",
                        std::vector<int>({3, 0, 7, 4, 1, 8, 5, 2, 9, 6})),
        std::make_tuple("test_input2.txt",
                        std::vector<int>({6, 3, 0, 7, 4, 1, 8, 5, 2, 9})),
        std::make_tuple("test_input3.txt",
                        std::vector<int>({9, 2, 5, 8, 1, 4, 7, 0, 3, 6}))));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
