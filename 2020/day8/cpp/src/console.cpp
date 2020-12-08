#include "console.hpp"

#include "utils.hpp"
Console::Console(std::string file_name)
    : program_m(),
      n_instructions_m(0),
      accumulator_m(0),
      offset_m(0),
      processed_instructions_m() {
  program_m = read_input(file_name);
  n_instructions_m = program_m.size();
}

void Console::reset() {
  accumulator_m = 0;
  offset_m = 0;
  processed_instructions_m = std::unordered_set<size_t>();
}

Console::input_type Console::transform_input(std::vector<std::string> input) {
  Console::input_type output;
  for (auto &inp : input) {
    std::vector<std::string> split;
    utils::split_string(inp, " ", split);
    output.push_back(std::make_pair(split[0], std::stoi(split[1])));
  }
  return output;
}

Console::input_type Console::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

std::pair<int, bool> Console::operator()() {
  while (true && offset_m < n_instructions_m) {
    auto op_val_pair = program_m[offset_m];

    if (processed_instructions_m.count(offset_m)) {
      auto output = accumulator_m;
      reset();
      return std::make_pair(output, false);
    }
    processed_instructions_m.insert(offset_m);

    if (op_val_pair.first == "acc") {
      accumulator_m += op_val_pair.second;
    } else if (op_val_pair.first == "jmp") {
      offset_m += op_val_pair.second - 1;
    }
    offset_m++;
  }

  auto output = accumulator_m;
  reset();
  return std::make_pair(output, true);
}