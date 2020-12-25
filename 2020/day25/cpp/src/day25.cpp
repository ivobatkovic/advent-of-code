#include "day25.hpp"

#include "utils.hpp"

using day25::input_type;
using day25::output_type;

input_type day25::transform_input(std::vector<std::string> &input) {
  input_type output;
  for (auto &inp : input) {
    output.push_back(std::stoi(inp));
  }
  return output;
}

input_type day25::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day25::solve_part1(const input_type &input_) {
  std::vector<int> loop_sizes;

  for (auto &public_key : input_) {
    int loop_size(0), val(1);
    while (true) {
      if (val == public_key) {
        break;
      }
      val = (val * 7) % 20201227;
      loop_size++;
    }
    loop_sizes.push_back(loop_size);
  }

  auto subject_nr = input_.front();
  auto loop_size = loop_sizes.back();

  int64_t val(1);
  for (int i = 0; i < loop_size; i++) {
    val = (val * subject_nr) % 20201227;
  }
  return val;
}
