#ifndef _ASCI_H_
#define _ASCI_H_

#include <map>
#include <utility>

#include "intcode.hpp"

class Asci {
 public:
  std::string m_file_name;
  Intcode m_intcode;
  std::map<std::pair<int, int>, int> m_mp;

  /**
   * @brief Construct a new Asci object
   *
   * @param file_name
   */
  Asci(std::string file_name);

  /**
   * @brief Initialize the map
   *
   * @return std::map<std::pair<int, int>, int>
   */
  std::map<std::pair<int, int>, int> get_map();

  /**
   * @brief Find all intersections on the map
   *
   * @param print_map
   * @return int
   */
  int compute_intersections(bool print_map = true);

  /**
   * @brief Print map
   *
   */
  void print_map();

  /**
   * @brief Go through the map and figure out starting pose
   *
   * @param x
   * @param y
   * @param theta
   */
  void find_start_pose(int &x, int &y, double &theta);

  /**
   * @brief Use the starting pose to prone the map and return the input
   * instructions needed to reach the end
   *
   * @return std::string
   */
  std::string traverse_scaffold();

  /**
   * @brief Compute the routine and sub-routines A,B,C
   *
   * @param routine
   * @param A
   * @param B
   * @param C
   */
  void find_movement_routine(std::string &routine, std::string &A,
                             std::string &B, std::string &C);

  /**
   * @brief Compute the intcode input
   *
   * @param print_iterations
   * @return std::vector<int64_t>
   */
  std::vector<int64_t> construct_input(bool print_iterations = false);

  /**
   * @brief Solve part two by using the input routine and subroutines
   *
   * @param print_iterations
   * @return int
   */
  int collect_dust(bool print_iterations = false);

  /**
   * @brief Print the robot collecting dust
   *
   * @return * int
   */
  int print_video_feed();

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