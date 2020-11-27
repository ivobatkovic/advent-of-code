#ifndef _BEAM_H_
#define _BEAM_H_

#include "intcode.hpp"
#include <string>

/**
 * @brief Beam class
 * 
 */
class Beam {

  public:
    std::string m_file_name;
    Intcode m_intcode;

  public:

    /**
     * @brief Construct a new Beam object
     * 
     * @param file_name 
     */
    Beam(std::string file_name);

    /**
     * @brief Solve part one: scan a grid of grid_size x gid_size
     * 
     * @param grid_size 
     * @return int 
     */
    int part_one(int grid_size=50);

    /**
     * @brief Solve part two: look for a beam that fits in a square
     * 
     * @param square_size 
     * @return int 
     */
    int part_two(int square_size = 100);

};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif