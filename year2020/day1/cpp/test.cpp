#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/utils.hpp"
#include "year2020/day1/cpp/solutions.hpp"

using std::string;

namespace year2020 {

namespace day1 {

class TestYear2020Day1PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2020Day1PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2020/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2020Day1PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "514579")));

class TestYear2020Day1PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2020Day1PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2020/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day1::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2020Day1PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "241861950")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day1

}  // namespace year2020
