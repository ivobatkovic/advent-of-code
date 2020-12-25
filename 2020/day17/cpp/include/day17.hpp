#ifndef _DAY17_H_
#define _DAY17_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <array>
#include <string>
#include <unordered_set>
#include <vector>

namespace day17 {

// Hash function for array keys
struct ArrayHasher {
  std::size_t operator()(const std::array<int, 4> &a) const {
    std::size_t h = 0;
    for (auto e : a) {
      h ^= std::hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
  }
};

using set_type = std::unordered_set<std::array<int, 4>, ArrayHasher>;
using output_type = int;
using input_type = std::vector<std::string>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

set_type get_potential_pos(set_type active, set_type dirs);
int simulate(input_type input, int ndim);
output_type solve_part1(const input_type &input);

output_type solve_part2(const input_type &input);
}  // namespace day17

#endif
