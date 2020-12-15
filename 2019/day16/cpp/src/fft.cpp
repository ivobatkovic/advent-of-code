#include "fft.hpp"

#include <math.h>

#include "utils.hpp"

// Read the input file and cast it into a vector of integers
FFT::FFT(std::string file_name) : m_input(), m_digit() {
  auto x = utils::read_file(file_name);

  m_input = x[0];
  for (auto &dig : x[0]) {
    m_digit.push_back(int(dig) - 48);
  }
}

std::string FFT::part_one(int n_updates) {
  // Number of digits
  auto N = m_digit.size();

  // FFT filter
  std::vector<int> filter({0, 1, 0, -1});

  // Go through the digits and apply the filter
  auto d = m_digit;
  for (int j = 0; j < n_updates; j++) {
    auto dig_ = d;
    for (size_t k = 0; k < N; k++) {
      int s(0);
      for (size_t i = 0; i < N; i++) {
        s += filter[(i + 1) / (k + 1) % 4] * d[i];
      }
      dig_[k] = std::abs(s) % 10;
    }
    d = dig_;
  }

  // Select the first 8 digits
  std::string output = "";
  for (int i = 0; i < 8; i++) {
    output += std::to_string(d[i]);
  }
  return output;
}

// Assumes structure on the input
std::string FFT::part_two() {
  auto d = m_digit;

  // Number of digits to skip
  auto d_skip = std::stoi(m_input.substr(0, 7));

  // Number of times to repeat the digit
  size_t const repeat = 10000;

  // If the digits we want to skip is on the second half, everything before it
  // will be zero
  if (d.size() * repeat < std::size_t(2 * d_skip)) {
    // Expand the digits repeat number of times
    d.reserve(d.size() * repeat);
    auto end = std::end(d);
    for (std::size_t i = 1; i < repeat; i++) {
      d.insert(std::end(d), std::begin(d), end);
    }
    // Chop away <d_skip> digits
    std::vector<int> v(d.begin() + d_skip, d.end());

    // Perform the FFT transform "reversely" for 100 steps
    for (int j = 0; j < 100; j++) {
      // Go backwards through the FFT
      for (size_t i = v.size() - 1; i > 0; i--) {
        v[i - 1] = (v[i - 1] + v[i]) % 10;
      }
    }

    // Return the 8 digits
    std::string output = "";
    for (int i = 0; i < 8; i++) {
      output += std::to_string(v[i]);
    }
    return output;
  }

  return "Need to brute force";
}
