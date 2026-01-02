#include "year2019/day2/cpp/solutions.hpp"

#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace year2019 {

namespace day2 {

using namespace std;
using input_type = vector<int32_t>;

class Intcode {
   public:
    Intcode(input_type const &prog) : prog_{prog} { run(); }

    int32_t get_exit_code() const { return prog_.at(0U); }

   private:
    void run() {
        while (true) {
            int32_t op = prog_.at(i_);
            if (op == 99) {
                return;
            }

            size_t const a = static_cast<size_t>(prog_.at(i_ + 1U));
            size_t const b = static_cast<size_t>(prog_.at(i_ + 2U));
            size_t const dst = static_cast<size_t>(prog_.at(i_ + 3U));

            if (op == 1) {
                prog_.at(dst) = prog_.at(a) + prog_.at(b);
            } else if (op == 2) {
                prog_.at(dst) = prog_.at(a) * prog_.at(b);
            }

            i_ += 4U;
        }
    }
    input_type prog_{};
    size_t i_{0U};
};

static input_type transform_input(const string &input_string) {
    return utils::split_string<int32_t>(input_string, ",");
}

std::string solve_part1(const string &input_string, bool const modify) {
    auto input = transform_input(input_string);
    if (modify) {
        input.at(1U) = 12;
        input.at(2U) = 2;
    }
    Intcode const ic(input);
    return to_string(ic.get_exit_code());
}

std::string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);

    for (int32_t noun{0}; noun < 100; ++noun) {
        for (int32_t verb{0}; verb < 100; ++verb) {
            input.at(1) = noun;
            input.at(2) = verb;
            if (Intcode(input).get_exit_code() == 19690720) {
                return to_string(100 * noun + verb);
            }
        }
    }
    return "0";
}
}  // namespace day2

}  // namespace year2019
