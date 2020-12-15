#include "cryo.hpp"

#include <iostream>

Cryo::Cryo(std::string file_name) : m_intcode(file_name, {}, false, false) {}

void Cryo::play() {
  std::vector<std::string> message;
  std::string row("");

  while (true) {
    auto output = m_intcode();

    if (std::get<1>(output) == -WINT_MAX) {
      // Print out the new screen
      for (auto &row_ : message) {
        std::cout << row_ << std::endl;
      }

      // Read input command and pass it to the intcode
      std::string input;
      std::getline(std::cin, input);

      for (auto &chr : input) {
        m_intcode.m_input.push_back(int(chr));
      }
      m_intcode.m_input.push_back(int('\n'));

      // Check if we want to quit
      if (char(m_intcode.m_input[0]) == 'q') {
        return;
      }

      // Clear the message
      message.clear();
      row = "";

      m_intcode.m_idle = false;

    } else {
      if (std::get<1>(output) == 10) {
        message.push_back(row);
        row = "";
      } else {
        row += char(std::get<1>(output));
      }
    }
  }
}