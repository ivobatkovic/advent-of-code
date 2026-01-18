#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <utility>

#include "utils/utils.hpp"
#include "year2019/day5/cpp/solutions.hpp"

using std::string;

namespace year2019 {

namespace day5 {

class TestYear2019Day5PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2019Day5PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2019/day5/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output, day5::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2019Day5PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "1")));

class TestYear2019Day5PartTwo
    : public ::testing::TestWithParam<
          std::tuple<string, std::pair<int32_t, string>>> {};

TEST_P(TestYear2019Day5PartTwo, PartTwo) {
    auto param = GetParam();
    auto file_name = "year2019/day5/data/" + std::get<0>(param);
    auto const &[input_list, output] = std::get<1>(param);
    EXPECT_EQ(output, day5::solve_part2(utils::read_file_to_string(file_name),
                                        {input_list}));
}

INSTANTIATE_TEST_SUITE_P(
    PartTwo, TestYear2019Day5PartTwo,
    ::testing::Values(
        std::make_tuple("test_input1.txt", std::make_pair(6, "999")),
        std::make_tuple("test_input1.txt", std::make_pair(8, "1000")),
        std::make_tuple("test_input1.txt", std::make_pair(10, "1001"))));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day5

}  // namespace year2019
