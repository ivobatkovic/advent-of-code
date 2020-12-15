#include "springdroid.hpp"

#include <iostream>

#include "intcode.hpp"

Springdroid::Springdroid(std::string file_name) : m_file_name(file_name) {}

int Springdroid::part_one() {
  std::vector<std::string> program({"NOT B T\n", "AND D T\n", "OR T J\n",
                                    "NOT C T\n", "AND D T\n", "OR T J\n",
                                    "NOT A T\n", "OR T J\n", "WALK\n"});

  return solve_program(program);
}

int Springdroid::part_two() {
  std::vector<std::string> program(
      {"NOT B T\n", "AND D T\n", "OR T J\n", "NOT C T\n", "AND D T\n",
       "AND H T\n", "OR T J\n", "NOT A T\n", "OR T J\n", "RUN\n"});
  return solve_program(program);
}

int Springdroid::solve_program(std::vector<std::string> program) {
  // Convert the program to input
  std::vector<int64_t> input;

  for (auto &letter : program) {
    for (auto &asci : letter) {
      input.push_back(int(asci));
    }
  }
  Intcode intcode(m_file_name, input, false, false);

  std::vector<std::string> message;
  std::string row_message("");

  // Run until termination
  while (true) {
    auto output = intcode();
    auto out = std::get<1>(output);

    // If terminated
    if (std::get<0>(output)) {
      for (auto &row : message) {
        std::cout << row << "\n";
      }
      return -1;
      // If output is non-asci we are done
    } else if (out > 255) {
      return out;
    } else if (out != 10) {
      row_message += char(out);
    } else {
      message.push_back(row_message);
      row_message = "";
    }
  }
}