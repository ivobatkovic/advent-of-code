#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <string>
#include <unordered_set>
#include <vector>

class Console {
  using input_type = std::vector<std::pair<std::string, int>>;

 public:
  input_type program_m;
  size_t n_instructions_m;
  int accumulator_m;
  size_t offset_m;
  std::unordered_set<size_t> processed_instructions_m;

  Console(std::string file_name = "../data/input.txt");
  void reset();
  input_type transform_input(std::vector<std::string> input);
  input_type read_input(std::string file_name);
  std::pair<int, bool> operator()();
};

#endif