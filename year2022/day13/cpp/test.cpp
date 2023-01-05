#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day13/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day13 {

class TestYear2022Day13PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day13PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2022/day13/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day13::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2022Day13PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "13")));

class TestYear2022Day13PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day13PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2022/day13/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day13::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2022Day13PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "140")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day13

}  // namespace year2022
