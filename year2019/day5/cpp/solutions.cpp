#include "year2019/day5/cpp/solutions.hpp"

#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2019 {

namespace day5 {

using namespace std;
using input_type = vector<int32_t>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<int32_t>(input_string, ",");
}

class Intcode {
   public:
    Intcode(input_type const &program) : prog_{program} {}

    int32_t operator()(input_type const &input_list) {
        size_t input_list_idx{};
        while (true) {
            auto const &[op, mode1, mode2] = get_opcodes();

            if (op == 99) {
                return output_;
            } else if (op == 1 || op == 2 || op == 7 || op == 8) {
                int32_t const val1 = get_value(i_ + 1U, mode1);
                int32_t const val2 = get_value(i_ + 2U, mode2);
                size_t const dst = static_cast<size_t>(prog_.at(i_ + 3U));

                prog_.at(dst) = operate(op, val1, val2);
                i_ += 4U;
            } else if (op == 3) {
                prog_.at(static_cast<size_t>(prog_.at(i_ + 1U))) =
                    input_list.at(input_list_idx++);
                i_ += 2U;
            } else if (op == 4) {
                output_ = get_value(i_ + 1, mode1);
                i_ += 2U;
            } else if (op == 5 || op == 6) {
                int32_t const val1 = get_value(i_ + 1U, mode1);
                int32_t const val2 = get_value(i_ + 2U, mode2);
                i_ = static_cast<size_t>(operate(op, val1, val2));
            }
        }
    }

   private:
    int32_t operate(int32_t const op, int32_t const val1, int32_t const val2) {
        if (op == 1)
            return val1 + val2;
        else if (op == 2)
            return val1 * val2;
        else if (op == 5)
            return (val1 != 0) ? val2 : static_cast<int32_t>(i_ + 3U);
        else if (op == 6)
            return (val1 == 0) ? val2 : static_cast<int32_t>(i_ + 3U);
        else if (op == 7)
            return val1 < val2;
        else if (op == 8)
            return val1 == val2;
        else
            return 0;
    }

    int32_t get_value(size_t const offset, int32_t const mode) {
        int32_t val = prog_.at(offset);
        return (mode) ? val : prog_.at(static_cast<size_t>(val));
    }
    array<int32_t, 3U> get_opcodes() {
        int32_t const opcode = prog_.at(i_);
        return {opcode % 100, (opcode / 100) % 10, (opcode / 1000) % 10};
    }

    input_type prog_;
    size_t i_{};
    int32_t output_{};
};

std::string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    Intcode intcode(input);
    input_type input_list{1};
    return to_string(intcode(input_list));
}

std::string solve_part2(const string &input_string,
                        vector<int32_t> const &input_list) {
    auto input = transform_input(input_string);
    Intcode intcode(input);
    return to_string(intcode(input_list));
}

}  // namespace day5

}  // namespace year2019
