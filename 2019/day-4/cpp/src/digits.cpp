#include "digits.hpp"

using std::string;

Digits::Digits() {}

bool Digits::double_digit(std::string num) {
  for(unsigned int i = 0; i < num.length()-1; i++) {
    if (num[i] == num[i+1])
      return true;
  }
  return false;
}

bool Digits::double_digit_no_adjacent(std::string num) {

  for(unsigned int i = 0; i < num.length()-1; i++) {
    if (num[i] == num[i+1]) {
      // Special case in the beginning of the number
      if (i==0 && (num[i+1] != num[i+2])) {
        return true;
      }
      if(i>0) {
        // Special case in the end of the number
        if ((i==num.length()-2) && (num[i-1] != num[i])){
          return true;
        }
        // Somwhere in the middle of the number
        else if ((num[i-1] != num[i]) && (num[i+1] != num[i+2])) {
          return true;
        }
      }
    }
  }
  return false;
}

std::string Digits::make_monotonic(std::string start_) {
  for (unsigned int i = 0; i < start_.length()-1; i++) {
    char dig1(start_[i]); char dig2(start_[i+1]);
    if (std::atoi(&dig1) > std::atoi(&dig2)) {
      for (unsigned int j = 0; j < start_.length(); j++) {
        start_[j] = start_[i];
      }
      return start_;
    }
  }
  return start_;
}

std::string Digits::next_monotonic(std::string num) {
  for(int i = (int)num.length()-1; i > -1; i--) {
    char dig(num[i]);
    if (std::atoi(&dig) < 9) {
      num[i] = dig+1;
      for(unsigned int j = i; j < num.length(); j++) {
        num[j] = num[i];
      }
      return num;
    }
  }
  return num;
}
