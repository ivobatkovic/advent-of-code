#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day24/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day24 {

class TestYear2022Day24PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day24PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2022/day24/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day24::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2022Day24PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "18")));

class TestYear2022Day24PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day24PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2022/day24/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day24::solve_part2(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestYear2022Day24PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "54")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day24

}  // namespace year2022
