#include "day8.hpp"

#include "console.hpp"
#include "utils.hpp"

using day8::input_type;

input_type day8::read_input(std::string file_name) { return file_name; }

// Implement part one solution
std::string day8::solve_part1(input_type input_) {
  Console console(input_);
  auto output = console();
  return std::to_string(output.first);
}

// Implement part two solution
std::string day8::solve_part2(input_type input_) {
  Console console(input_);
  for (auto &inp : console.program_m) {
    auto op = inp.first;
    if (op == "nop") {
      inp.first = "jmp";
    } else if (op == "jmp") {
      inp.first = "nop";
    }

    auto output = console();
    if (output.second) {
      return std::to_string(output.first);
    }
    inp.first = op;
  }
  return "Failed to find solution";
}
