#include "intcode.hpp"

#include <iostream>
#include <numeric>

#include "utils.hpp"

using std::tuple;

Intcode::Intcode(bool reset, bool verbose)
    : m_program(),
      m_input(),
      m_iter(0),
      m_base(0),
      m_output(0),
      m_reset(reset),
      m_verbose(verbose),
      m_idle(false) {}

Intcode::Intcode(std::string file_name, std::vector<int64_t> input, bool reset,
                 bool verbose)
    : m_program(),
      m_input(input),
      m_iter(0),
      m_base(0),
      m_output(0),
      m_reset(reset),
      m_verbose(verbose),
      m_idle(false) {
  // Read the program
  std::vector<std::string> file_contents = utils::read_file(file_name);
  auto file_concat = std::accumulate(file_contents.begin(), file_contents.end(),
                                     std::string(""));
  std::vector<int64_t> input_file;
  utils::split_string(file_concat, ",", input_file);
  for (auto &inp : input_file) {
    m_program.push_back(inp);
  }
}

// Parse the incoming operation with its operands
tuple<char, int64_t, int64_t, int64_t> Intcode::parse_opcode(std::string op) {
  // Get the operation
  auto oper = op.back();

  // Extract the mode of the operations - pad with zeros to simplify
  auto mode = "000" + op.substr(0, std::max(int(op.length() - 2), 0));
  auto mode_len = mode.length() - 1;

  // Temporary iterating index
  auto j = m_iter;

  // Set base offsets for the out, p2, and p1
  auto b0 = (mode[mode_len] == '2') ? m_base : 0;
  auto b1 = (mode[mode_len - 1] == '2') ? m_base : 0;
  auto b2 = (mode[mode_len - 2] == '2') ? m_base : 0;

  auto b0x = b0 + m_program[j + 1];
  auto b1x = b1 + m_program[j + 2];

  auto xb0 = (b0x >= int64_t(m_program.size()) || b0x < 0) ? 0 : m_program[b0x];
  auto xb1 = (b1x >= int64_t(m_program.size()) || b1x < 0) ? 0 : m_program[b1x];

  /* Set what the operation parameters will be: either its value or
  value at program address. */
  if (oper == '1' || oper == '2' || oper == '7' || oper == '8') {
    int64_t p1 = (mode[mode_len] == '1') ? m_program[j + 1] : xb0;
    int64_t p2 = (mode[mode_len - 1] == '1') ? m_program[j + 2] : xb1;
    int64_t out = b2 + m_program[j + 3];
    m_iter += 4;
    return std::make_tuple(oper, p1, p2, out);
  } else if (oper == '5' or oper == '6') {
    int64_t p1 = (mode[mode_len] == '1') ? m_program[j + 1] : xb0;
    int64_t p2 = (mode[mode_len - 1] == '1') ? m_program[j + 2] : xb1;
    m_iter += 3;
    return std::make_tuple(oper, p1, p2, -1);
  } else if (oper == '4') {
    auto p = (mode[mode_len] == '1') ? m_program[j + 1] : xb0;
    m_iter += 2;
    return std::make_tuple(oper, p, -1, -1);
  } else if (oper == '9') {
    auto base_ = (mode[mode_len] == '1') ? m_program[j + 1] : xb0;
    m_iter += 2;
    m_base += base_;
    return std::make_tuple(' ', -1, -1, -1);
  } else {
    auto p = b0 + m_program[j + 1];
    m_iter += 2;
    return std::make_tuple(oper, p, -1, -1);
  }
}

// Apply the operations
void Intcode::operate(char oper, int64_t p1, int64_t p2, int64_t out) {
  // If we need to store memory outside our program, resize.
  if (out >= int64_t(m_program.size())) {
    if (oper == '1' || oper == '2' || oper == '7' || oper == '8') {
      m_program.resize(out * 2);
    }
  }

  if (oper == '1') {
    m_program[out] = p1 + p2;
  } else if (oper == '2') {
    m_program[out] = p1 * p2;
  } else if (oper == '3') {
    // If obtained an input instruction, but did not provide one, go idle.
    if (m_input.size() == 0) {
      m_input.push_back(-1);
      m_idle = true;
    }
    if (p1 >= int64_t(m_program.size())) {
      m_program.resize(2 * p1);
    }
    m_program[p1] = m_input.front();
    m_input.erase(m_input.begin());
  } else if (oper == '4') {
    m_output = p1;
    if (m_verbose) {
      std::cout << p1 << "\n";
    }
  } else if (oper == '5') {
    m_iter = (p1 != 0) ? p2 : m_iter;
  } else if (oper == '6') {
    m_iter = (p1 == 0) ? p2 : m_iter;
  } else if (oper == '7') {
    m_program[out] = (p1 < p2) ? 1 : 0;
  } else if (oper == '8') {
    m_program[out] = (p1 == p2) ? 1 : 0;
  }
}

/* Operator () runs the program until termination and returns what is at
program adress 0 */
tuple<bool, int64_t> Intcode::operator()(int64_t input) {
  return (*this)(std::vector<int64_t>{input});
}

tuple<bool, int64_t> Intcode::operator()(std::vector<int64_t> input) {
  // Append new inputs
  for (auto i : input) {
    m_input.push_back(i);
  }

  // Copy original program incase it needs to be reset
  auto x = m_program;

  while (m_iter < m_program.size()) {
    if (m_program[m_iter] == 99) {
      m_iter = 0, m_base = 0;
      m_program = m_reset ? x : m_program;
      return std::make_tuple(true, m_output);
    }

    // oper, p1, p2, out
    tuple<char, int64_t, int64_t, int64_t> op =
        parse_opcode(std::to_string(m_program[m_iter]));
    char oper = std::get<0>(op);
    int64_t p1 = std::get<1>(op), p2 = std::get<2>(op), out = std::get<3>(op);

    // Temporary output which is nonsense
    if (oper == '3' && m_idle) {
      return std::make_tuple(false, -WINT_MAX);
    }

    operate(oper, p1, p2, out);

    if (!m_reset && oper == '4') {
      return std::make_tuple(false, m_output);
    }
  }
  return std::make_tuple(false, m_output);
}