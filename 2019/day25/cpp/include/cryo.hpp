#ifndef _CRYO_H_
#define _CRYO_H_

#include "intcode.hpp"
#include <string>

/**
 * @brief Cryo class
 * 
 */
class Cryo {

  public:
    Intcode m_intcode;

    /**
     * @brief Construct a new Cryo object
     * 
     * @param file_name 
     */
    Cryo(std::string file_name);

    /**
     * @brief Play the game
     * 
     */
    void play();
    
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif