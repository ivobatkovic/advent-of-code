#ifndef _SPRINGDROID_H_
#define _SPRINGDROID_H_

#include <string>
#include <vector>

/**
 * @brief Springdroid class
 * 
 */
class Springdroid {

  public:
    std::string m_file_name;

    /**
     * @brief Construct a new Springdroid object
     * 
     * @param file_name 
     */
    Springdroid(std::string file_name);

    /**
     * @brief Generate program for part one
     * 
     * @return int 
     */
    int part_one();

    /**
     * @brief Generate program for part two
     * 
     * @return int 
     */
    int part_two();

    /**
     * @brief Use the program to solve the problem
     * 
     * @param program 
     * @return int 
     */
    int solve_program(std::vector<std::string> program);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif