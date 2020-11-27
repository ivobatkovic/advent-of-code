#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <string>

/**
 * @brief Amplifier class
 * 
 */
class Amplifier {

  public:
  
    /**
     * @brief Construct a new Amplifier object
     * 
     */
    Amplifier();

    /**
     * @brief Get the maximum thrust from all phases
     * 
     * @param file_name 
     * @return int 
     */
    static int get_maximum_thrust(std::string file_name);

    /**
     * @brief Get maximum feedback thrust from all phases
     * 
     * @param file_name 
     * @return int 
     */
    static int feedback_thrust(std::string file_name);


};



#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif