#include "year2022/day10/cpp/solutions.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day10 {

using namespace std;
using input_type = vector<string>;

static input_type transform_input(const string &input_string) {
    return utils::split_string<string>(input_string, "\n");
}

class CRT {
   public:
    CRT(input_type const &input) {
        for (auto &row : input) {
            if ("noop" == row.substr(0, 4)) {
                update();
            } else {
                update(2);
                add(stoi(row.substr(5, row.length() - 5)));
            }
        }
    }

    int get_signal() { return signal_; }
    string get_output() { return output_; }

   private:
    void update(size_t n_updates = 1) {
        for (size_t i{0U}; i < n_updates; ++i) {
            if (cycle_ % 40 == 0) {
                output_ += '\n';
            }

            if ((cycle_ + 1 - 20) % 40 == 0) {
                signal_ += (cycle_ + 1) * x_;
            }

            if (abs(cycle_ % 40 - x_) <= 1) {
                output_ += '#';
            } else {
                output_ += '.';
            }

            cycle_++;
        }
    }

    void add(int val) { x_ += val; }
    int x_{1};
    int cycle_{};
    int signal_{};
    string output_{};
};

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);
    CRT crt(input);
    return to_string(crt.get_signal());
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    CRT crt(input);
    return crt.get_output();
}

}  // namespace day10

}  // namespace year2022
