#include <cstdint>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "utils.hpp"

using std::string;

namespace utils {

namespace test {

class TestUtils : public ::testing::Test {};

using ::testing::FloatNear;
using ::testing::Pointwise;

TEST_F(TestUtils, abcSplitString) {
    std::string abc_str = "a,b,c";
    auto output_str_delim = utils::split_string<std::string>(abc_str, ",");
    auto output_chr_delim = utils::split_string<std::string>(abc_str, ',');

    std::vector<std::string> expected{"a", "b", "c"};

    EXPECT_EQ(output_str_delim, expected);
    EXPECT_EQ(output_chr_delim, expected);
}

TEST_F(TestUtils, numericSplitString) {
    std::string numeric_str = "1.0,2.2,-5.3";
    auto output_int = utils::split_string<std::int32_t>(numeric_str, ",");
    auto output_float = utils::split_string<float>(numeric_str, ",");

    std::vector<int32_t> expected_int{1, 2, -5};
    std::vector<float> expected_float{1.0F, 2.2F, -5.3F};

    EXPECT_EQ(output_int, expected_int);
    EXPECT_THAT(output_float, Pointwise(FloatNear(1e-6F), expected_float));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace test

}  // namespace utils
