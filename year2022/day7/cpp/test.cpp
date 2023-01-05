#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day7/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day7 {

class TestYear2022Day7PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day7PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2022/day7/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day7::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2022Day7PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "95437")));

class TestYear2022Day7PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day7PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2022/day7/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day7::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2022Day7PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "24933642")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day7

}  // namespace year2022
