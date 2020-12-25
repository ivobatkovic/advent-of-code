#ifndef _DAY24_H_
#define _DAY24_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <string>
#include <unordered_set>
#include <vector>
namespace day24 {

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

// Default input type for each day: need to change
using output_type = int;
using input_type = std::vector<std::vector<std::string>>;
using set_type = std::unordered_set<std::pair<int, float>, pair_hash>;
using vector_type = std::vector<std::pair<int, float>>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

set_type traverse(const input_type &input_);
output_type solve_part1(const input_type &input);

set_type get_active(set_type &tile, vector_type &neighbors);
output_type solve_part2(const input_type &input);
}  // namespace day24

#endif
