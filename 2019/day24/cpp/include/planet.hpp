#ifndef _PLANET_H_
#define _PLANET_H_

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

/**
 * @brief Structure with default empty grid 5 x "....." grid
 *
 */
struct grid_struct {
  std::vector<std::string> data = std::vector<std::string>(5, {"....."});
  grid_struct(std::vector<std::string> n1) : data(n1) {}
  grid_struct() : data(5, {"....."}) {}
};

/**
 * @brief Planet class
 *
 */
class Planet {
 public:
  std::vector<std::string> m_empty_grid;
  std::map<int, grid_struct> m_grid;
  int m_h, m_w;
  bool m_recursive;
  std::map<std::tuple<int, int>, std::vector<std::vector<int>>> m_neighbors_map;
  std::set<std::string> m_map_config;

  /**
   * @brief Construct a new Planet object
   *
   * @param file_name
   * @param recursive
   */
  Planet(std::string file_name, bool recursive = false);

  /**
   * @brief Compute the neighbors object
   *
   */
  void compute_neighbors();

  /**
   * @brief Perform one update of the system
   *
   * @param n_updates
   * @return true
   * @return false
   */
  bool update(int n_updates = 1);

  /**
   * @brief Return the map structure
   *
   * @param file_name
   * @return std::map<int,grid_struct>
   */
  std::map<int, grid_struct> read_map(std::string file_name);

  /**
   * @brief Solve part one
   *
   * @return int
   */
  int part_one();

  /**
   * @brief Solve part two
   *
   * @param n_steps
   * @return int
   */
  int part_two(int n_steps = 200);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif