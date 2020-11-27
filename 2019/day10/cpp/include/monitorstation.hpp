#ifndef _MONITORSTATION_H_
#define _MONITORSTATION_H_

#include <string>
#include <vector>
#include <tuple>

/**
 * @brief MonitorStation class
 * 
 */
class MonitorStation
{
  public:
    std::vector<std::string> m_input;
    MonitorStation(std::string m_file_name);

    /**
     * @brief Returns all pairs (x,y) where an asteroid is ('#')
     * 
     * @param x input grid/map
     * @return std::vector<std::vector<std::size_t>> 
     */
    std::vector<std::vector<std::size_t>> 
        find_asteroids(std::vector<std::string> grid);

    /**
     * @brief Iterates over the vectors<{distance,x,y}> and returns the 
     * index with smallest distance
     * 
     * @param grid 
     * @return int 
     */
    int find_closest(std::vector<std::vector<double>> asteroids);

    /**
     * @brief Solves part one by looping through the grid and stores all 
     * unique angles to an asteroid. Returns the x,y coordinate with the most
     * detections
     * 
     * @param grid input
     * @return std::tuple<int, int> x,y coordinte
     */
    std::tuple<int, int> compute_vision(std::vector<std::string> grid);

    /**
     * @brief Loops through the asteroid map in a clock-wise manner and removes
     * asteroids
     * 
     * @param grid input
     * @param asteroid_index starting point of asteroid
     * @param number how many asteroids to destory
     * @return int 
     */
    int blast(std::vector<std::string> grid, int asteroid_index, int number);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif