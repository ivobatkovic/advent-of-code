#ifndef _DROID_H_
#define _DROID_H_

#include <map>

#include "intcode.hpp"

/**
 * @brief Droid class
 *
 */
class Droid {
 public:
  Intcode m_intcode;
  std::map<std::pair<int, int>, int> m_map;

  /**
   * @brief Construct a new Droid object
   *
   * @param file_name
   */
  Droid(std::string file_name);

  /**
   * @brief  Return new step depending on input
   *
   * @param x
   * @param y
   * @param input
   * @return std::pair<int,int>
   */
  std::pair<int, int> one_step(int x, int y, int input);

  /**
   * @brief Solve part one: explore the map generated from the intcode
   *
   * @param y
   * @param x
   * @return std::tuple<int,int,int>
   */
  std::tuple<int, int, int> repair_oxygen(int y = 0, int x = 0);

  /**
   * @brief Solve part two: traverse through the map and fill it up
   *
   * @param y
   * @param x
   * @return int
   */
  int fill_oxygen(int y = 0, int x = 0);

  /**
   * @brief Print the map
   *
   */
  void render();

  /**
   * @brief Catch a ctrl-c event
   *
   * @param s
   */
  [[noreturn]] static void catch_ctrlc(int s);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif