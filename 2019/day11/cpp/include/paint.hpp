#ifndef _PAINT_H_
#define _PAINT_H_

#include <string>
#include <unordered_map>

#include "2019/day5/cpp/include/intcode.hpp"

/**
 * @brief Hash function to handle pairs of keys
 *
 */
struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2> &p) const {
    return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
  }
};

typedef std::unordered_map<std::pair<int, int>, std::string, hash_pair> pairmap;

/**
 * @brief Paint class
 *
 */
class Paint {
 public:
  /**
   * @brief Construct a new Paint object
   *
   */
  Paint();

  /**
   * @brief Runs the intcode program and returns how many tiles were painted
   *
   * @param map
   * @param intcode
   * @return int number of painted tiles
   */
  static int get_painted_tiles(pairmap &map, Intcode &intcode);

  /**
   * @brief Print the contents of the map
   *
   * @param map
   */
  static void paint_map(pairmap map);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif