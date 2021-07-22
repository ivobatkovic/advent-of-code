#include "2019/day4/cpp/include/digits.hpp"

#include <iostream>

using std::string;

Digits::Digits() {}

bool Digits::double_digit(std::string num) {
  // Check if neighboring digit is the same
  for (std::size_t i = 0; i < num.length() - 1; i++) {
    if (num[i] == num[i + 1]) return true;
  }
  return false;
}

bool Digits::double_digit_no_adjacent(std::string num) {
  for (std::size_t i = 0; i < num.length() - 1; i++) {
    // Check that there are no numbers left or right of this combination
    if (num[i] == num[i + 1]) {
      // Special case in the beginning of the number
      if (i == 0 && num[i + 1] != num[i + 2]) {
        return true;
      }
      // Special case in the end of the number
      if (i == num.length() - 2 && num[i - 1] != num[i]) {
        return true;
      }
      // Somwhere in the middle of the number
      if (i > 0 && num[i - 1] != num[i] && num[i + 1] != num[i + 2]) {
        return true;
      }
    }
  }
  return false;
}

std::string Digits::make_monotonic(std::string start_) {
  for (std::size_t i = 0; i < start_.length() - 1; i++) {
    // Compare asci. If next digit is smaller, update it
    if (start_[i] > start_[i + 1]) {
      for (std::size_t j = i; j < start_.length(); j++) {
        start_[j] = start_[i];
      }
      return start_;
    }
  }
  return start_;
}

std::string Digits::next_monotonic(std::string num) {
  for (int i = (int)num.length() - 1; i > -1; i--) {
    if (num[i] < 9 + '0') {
      num[i] += 1;
      for (std::size_t j = i; j < num.length(); j++) {
        num[j] = num[i];
      }
      return num;
    }
  }
  return num;
}
