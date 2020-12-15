#ifndef _DIGITS_H_
#define _DIGITS_H_

#include <string>

class Digits {
 public:
  /**
   * @brief Construct a new Digits object
   *
   */
  Digits();

  /**
   * @brief Check if number has double digits
   *
   * @param num input
   * @return true
   * @return false
   */
  static bool double_digit(std::string num);

  /**
   * @brief Check if a double digit occurs without adjacent similar numbers.
   *
   * @param num
   * @return true
   * @return false
   */
  static bool double_digit_no_adjacent(std::string num);

  /**
   * @brief Convert number to closest monotonic number, e.g.,
   * 123->123, 243->244, 213->222
   *
   * @param start
   * @return std::string
   */
  static std::string make_monotonic(std::string start);

  /**
   * @brief Get the next monotonic number
   *
   * @param num
   * @return std::string
   */
  static std::string next_monotonic(std::string num);
};

#endif
