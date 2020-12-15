#ifndef _INTCODE_H_
#define _INTCODE_H_
#include <string>
#include <vector>

/**
 * @brief Class of Intcode computer
 *
 */
class Intcode {
 public:
  std::string m_file_name;
  std::vector<int> m_memory;
  bool m_reset;

 public:
  /**
   * @brief Construct a new Intcode object
   *
   * @param reset reset variable
   */
  Intcode(bool reset = true);

  /**
   * @brief Construct a new Intcode object
   *
   * @param file_name_ file location
   * @param reset  reset variable
   */
  Intcode(std::string file_name, bool reset = true);

  /**
   * @brief Operator to run the intcode program
   *
   * @return int
   */
  int operator()();
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif