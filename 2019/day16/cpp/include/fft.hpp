#ifndef _FFT_H_
#define _FFT_H_

#include <vector>
#include <string>

/**
 * @brief FFT class
 * 
 */
class FFT {

  public:
    std::string m_input;
    std::vector<int> m_digit;

    /**
     * @brief Construct a new FFT object
     * 
     * @param file_name 
     */
    FFT(std::string file_name);

    /**
     * @brief Solves part one by filtering the input
     * 
     * @param n_update 
     * @return std::string 
     */
    std::string part_one(int n_update=100);

    /**
     * @brief Solves part two by updating it from the rear. Assumes a structure
     * on the problem
     * 
     * @return std::string 
     */
    std::string part_two();
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif