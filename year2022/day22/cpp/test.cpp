#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "utils/cpp_utils.hpp"
#include "year2022/day22/cpp/solutions.hpp"

using std::string;

namespace year2022 {

namespace day22 {

class TestYear2022Day22PartOne
    : public ::testing::TestWithParam<std::tuple<string, string>> {};

TEST_P(TestYear2022Day22PartOne, PartOne) {
    auto param = GetParam();
    auto file_name = "year2022/day22/data/" + std::get<0>(param);
    auto output = std::get<1>(param);
    EXPECT_EQ(output,
              day22::solve_part1(utils::read_file_to_string(file_name)));
}

INSTANTIATE_TEST_SUITE_P(PartOne, TestYear2022Day22PartOne,
                         ::testing::Values(std::make_tuple("test_input0.txt",
                                                           "6032")));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace day22

}  // namespace year2022
