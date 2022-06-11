#include <gtest/gtest.h>

#include <string>
#include <tuple>

extern "C" {
#include "c_utils.h"
#include "solutions.h"
}

using std::string;

class TestDay1PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestDay1PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "2019/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);

    char *input = read_file_contents(file_name.c_str());
    char *result = Day1.solve_part1(input);
    EXPECT_EQ(output.c_str(), std::string(result));
    free(input);
    free(result);
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestDay1PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "1")));

class TestDay1PartTwo
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestDay1PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "2019/day1/data/" + std::get<0>(param);
    auto output = std::get<1>(param);

    char *input = read_file_contents(file_name.c_str());
    char *result = Day1.solve_part2(input);

    EXPECT_EQ(output, std::string(result));
    free(input);
    free(result);
}

INSTANTIATE_TEST_SUITE_P(PartTwo, TestDay1PartTwo,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "1")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
