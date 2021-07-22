#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <string>
#include <utility>
#include <vector>

#include "2019/day5/cpp/include/intcode.hpp"

/**
 * @brief Network class
 *
 */
class Network {
 public:
  std::string m_file_name;
  int m_num_nodes;
  std::vector<Intcode> m_nodes;

  /**
   * @brief Construct a new Network object
   *
   * @param file_name_
   * @param num_nodes
   */
  Network(std::string file_name_, int num_nodes);

  /**
   * @brief Initialize nods
   *
   * @return std::vector<Intcode>
   */
  std::vector<Intcode> initialize_nodes();

  /**
   * @brief Run the network
   *
   * @return std::pair<int, int>
   */
  std::pair<int, int> run();
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif