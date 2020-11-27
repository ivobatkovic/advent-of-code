#ifndef _INTCODE_H
#define _INTCODE_H

#include <string>
#include <vector>
#include <tuple>

/**
 * @brief Class of Intcode computer
 * 
 */
class Intcode
{
public:
  std::vector<int64_t> m_program, m_input;
  std::size_t m_iter;
  int64_t m_base, m_output;
  bool m_reset, m_verbose, m_idle;

public:

  /**
   * @brief Construct a new Intcode object
   * 
   * @param reset reset variable
   */
  Intcode(bool reset= true, bool verbose = true);

  /**
   * @brief Construct a new Intcode object
   * 
   * @param file_name_ file location
   * @param reset_  reset variable
   */
  Intcode(std::string file_name, std::vector<int64_t> input = {},
          bool reset = true, bool verbose = true);

  /**
   * @brief Operator to run the intcode program
   * 
   * @return int 
   */
  std::tuple<bool, int64_t> operator()(int64_t input);
  std::tuple<bool, int64_t> operator()(std::vector<int64_t> input = {});

private:
  /**
   * @brief Parse opcode and return the operators
   * 
   * @param op 
   * @return std::tuple<char, int64_t, int64_t, int64_t> 
   */
  std::tuple<char, int64_t, int64_t, int64_t> parse_opcode(std::string op);

  /**
   * @brief Apply the operations
   * 
   * @param oper 
   * @param p1 
   * @param p2 
   * @param out 
   */
  void operate(char oper, int64_t p1, int64_t p2, int64_t out);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif