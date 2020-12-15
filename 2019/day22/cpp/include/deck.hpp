#ifndef _DECK_H_
#define _DECK_H_

#include <string>
#include <utility>
#include <vector>

__extension__ typedef __int128 int128;

/**
 * @brief Deck class
 *
 */
class Deck {
 public:
  std::string m_file_name;
  int64_t m_num_cards;
  int64_t m_a;
  int64_t m_b;

  /**
   * @brief Construct a new Deck object
   *
   * @param file_name
   * @param num_cards
   */
  Deck(std::string file_name, int64_t num_cards);

  /**
   * @brief Read the input
   *
   * @return std::vector<std::pair<char, int>>
   */
  std::vector<std::pair<char, int>> read_shuffle();

  /**
   * @brief Parse the instructions into the linear transformation y=ax+b
   *
   * @param instructions
   * @param a
   * @param b
   */
  void parse(std::vector<std::pair<char, int>> instructions, int64_t &a,
             int64_t &b);

  /**
   * @brief Solve part one
   *
   * @param card
   * @return int
   */
  int part_one(int card);

  /**
   * @brief Solve part two
   *
   * @param card
   * @param n_shuffles
   * @return int64_t
   */
  int64_t part_two(int card, int64_t n_shuffles);

  /**
   * @brief Modulo operator that handles big numbers
   *
   * @param a
   * @param b
   * @return int128
   */
  inline int128 mod(int128 a, int128 b);

  /**
   * @brief Extended greatest common dividor
   *
   * @param a
   * @param b
   * @param x
   * @param y
   * @return int128
   */
  int128 gcd_extended(int128 a, int128 b, int128 &x, int128 &y);

  /**
   * @brief Performs the modular inverse (assumes specific properties)
   *
   * @param b
   * @param n
   * @return int128
   */
  int128 modular_inverse(int128 b, int128 n);

  /**
   * @brief Modular division by using modular inverse trick
   *
   * @param a
   * @param b
   * @param n
   * @return int128
   */
  int128 modular_divide(int128 a, int128 b, int128 n);

  /**
   * @brief Modular power implementation
   *
   * @param base
   * @param exponent
   * @param n
   * @return int128
   */
  int128 modular_power(int128 base, int128 exponent, int128 n);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif