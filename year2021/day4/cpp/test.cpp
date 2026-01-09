#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2021/day4/cpp/solutions.hpp"

using std::string;

namespace year2021 {

namespace day4 {

class TestYear2021Day4PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2021Day4PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2021/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2021Day4PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "4512")));

class TestYear2021Day4PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2021Day4PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2021/day4/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day4::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2021Day4PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "1924")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day4

}  // namespace year2021
