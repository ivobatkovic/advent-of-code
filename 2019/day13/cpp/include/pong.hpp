#ifndef _PONG_H_
#define _PONG_H_

#include <string>
#include <vector>
#include "intcode.hpp"
#include <unordered_map>

/**
 * @brief Hash function to handle pairs of keys
 * 
 */
struct hash_pair
{
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2> &p) const
  {
    return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
  }
};
/**
 * @brief Pong class
 * 
 */
class Pong {

  public:
    Intcode m_intcode;
    std::unordered_map<std::pair<int, int>, int, hash_pair> m_map;
    std::vector<int64_t> m_ball, m_pad;
    bool m_map_rendered, m_ball_rendered;
    int m_score;

    /**
     * @brief Construct a new Pong object
     * 
     * @param file_name 
     * @param play 
     */
    Pong(std::string file_name, bool play = false);

    
    /**
     * @brief Generate the map and count number of tiles
     * 
     */
    void render();

    /**
     * @brief Select an input to move left,right or stand still
     * 
     * @return int 
     */
    int bot();

    /**
     * @brief Run the game
     * 
     * @return int 
     */
    int play();

    /**
     * @brief Print the map contents
     * 
     * @return int 
     */
    int render_map();

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