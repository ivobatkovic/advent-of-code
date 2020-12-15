#ifndef _FORMULA_H_
#define _FORMULA_H_

#include <tuple>
#include <unordered_map>
#include <vector>
#include <string>

typedef std::vector<std::tuple<int, int, std::string>> tuple_vec;

/**
 * @brief Formula class
 *
 */
class Formula {
 public:
  std::unordered_map<std::string, tuple_vec> m_formula;

  /**
   * @brief Construct a new Formula object
   *
   * @param file_name
   */
  Formula(std::string file_name);

  /**
   * @brief Read input and set up the formula X AB, Y CD => Z EF into
   * left-hand and right-hand side
   *
   * @param file_name
   */
  void initialize_formula(std::string file_name);

  /**
   * @brief
   *
   * @param key
   * @param amount
   * @return int64_t
   */
  int64_t compute(std::string key, int64_t amount = 1);

  /**
   * @brief
   *
   * @param ore
   * @return int64_t
   */
  int64_t compute_fuel(int64_t ore = 1e12);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif