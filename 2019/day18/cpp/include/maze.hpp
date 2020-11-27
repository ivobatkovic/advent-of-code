#ifndef _MAZE_H_
#define _MAZE_H_

#include <set>
#include <tuple>
#include <vector>

/**
 * @brief Maze class
 * 
 */
class Maze {

  public:
    std::vector<std::string> m_grid;
    int m_y, m_x;
    std::set<char> m_total_keys;
    std::vector<std::pair<int, int>> m_pos;

    /**
     * @brief Construct a new Maze object
     * 
     * @param file_name 
     * @param multiple_robots 
     */
    Maze(std::string file_name, bool multiple_robots = false);

    /**
     * @brief Go through the maze and find the starting position + all keys
     * 
     */
    void find_start_and_keys();

    /**
     * @brief Modify map if multi_robots is true
     * 
     * @param multi_robots 
     * @return std::vector<std::pair<int, int>> 
     */
    std::vector<std::pair<int, int>> initialize_position(bool multi_robots);

    /**
     * @brief Return vector of of all reachable keys with each element
     * as <depth,y,x,key> elements
     * 
     * @param y 
     * @param x 
     * @param keys 
     * @return std::vector<std::tuple<int,int,int,char>> 
     */
    std::vector<std::tuple<int,int,int,char>> 
        reachable_keys(int y, int x, std::set<char> keys);

    /**
     * @brief Go through the maze and collect keys in a graph structure.
     * 
     * @return int 
     */
    int compute_shortest_path(); 
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif