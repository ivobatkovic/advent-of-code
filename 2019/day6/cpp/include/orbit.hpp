#ifndef _ORBIT_H_
#define _ORBIT_H_

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief Orbit class
 * 
 */
class Orbit {

  public:
    
    std::unordered_map<std::string,std::vector<std::string>> m_parents;
    std::unordered_map<std::string, std::vector<std::string>> m_neighbors;

    /**
     * @brief Construct a new Orbit object
     * 
     * @param file_name 
     */
    Orbit(std::string file_name);

    /**
     * @brief Get the number of orbits object
     * 
     * @return int 
     */
    int get_number_of_orbits();

    /**
     * @brief Get the orbitals object
     * 
     * @param start node
     * @param end node
     * @return int 
     */
    int get_orbitals(std::string start, std::string end);

};



#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif