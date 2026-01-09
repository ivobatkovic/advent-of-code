#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2015/day4/cpp/solutions.hpp"

using std::string;

namespace year2015 {

namespace day4 {

class TestYear2015Day4PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2015Day4PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2015/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day4::solve_part1(utils::read_file_to_string(file_name), 609000));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2015Day4PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "609043")));

class TestYear2015Day4PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2015Day4PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2015/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part2(utils::read_file_to_string(file_name),
                                        6742830));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2015Day4PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "6742839")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day4

}  // namespace year2015
