#ifndef _GRAVITY_H_
#define _GRAVITY_H_

#include <string>
#include <vector>

/**
 * @brief Gravity class
 *
 */
class Gravity {
 public:
  std::vector<std::vector<int>> m_pos, m_vel;
  std::vector<int> m_cycles;

  /**
   * @brief Construct a new Gravity object
   *
   * @param file_name
   */
  Gravity(std::string file_name);

  /**
   * @brief Update one time step for a dimension
   *
   * @param dim
   */
  void tick(int dim = 0);
  /**
   * @brief Update all dimensions for <time> timesteps
   *
   * @param time
   */
  void update(int time = 1);

  /**
   * @brief Compute the energy
   *
   * @return int energy
   */
  int energy();

  /**
   * @brief Compute cycles for all dimensions and compute the least common
   * multiple between them
   *
   * @return int64_t time it takes for the system to reset
   */
  int64_t compute_cycles();

  /**
   * @brief Greatest common divisor between a and b
   *
   * @param a
   * @param b
   * @return int64_t
   */
  int64_t greatest_common_divisor(int64_t a, int64_t b);

  /**
   * @brief Least common multiple between a and b
   *
   * @param a
   * @param b
   * @return int64_t
   */
  int64_t least_common_multiple(int64_t a, int64_t b);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif