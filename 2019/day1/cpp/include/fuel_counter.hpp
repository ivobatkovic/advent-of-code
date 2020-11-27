#ifndef _FUEL_COUNTER_H_
#define _FUEL_COUNTER_H_

#include <string>
#include <vector>

/**
 * @brief Class that handles solution of day 1
 * 
 */
class FuelCounter
{
  public:
    std::vector<int> m_masses;
    
  public:
    /**
     * @brief Construct a new Fuel Counter object
     * 
     */
    FuelCounter();
    
    /**
     * @brief Construct a new Fuel Counter object and read
     * input from file_name
     * 
     * @param file_name input file name
     */
    FuelCounter(std::string file_name);
    
    /**
     * @brief Computes fuel needed for a vector of masses
     * 
     * @param masses_ vector of input mass
     * @return int fuel needed
     */
    int fuel_counter(std::vector<int> & masses);

    /**
     * @brief Computes fuel needed for a single mass
     * 
     * @param mass input mass
     * @return int fuel needed
     */
    int fuel_counter(int mass);

    /**
     * @brief Computes fuel needed for masses, including the
     * fuel weight
     * 
     * @param masses_ vector of input mass
     * @return int fuel needed
     */
    int fuel_counter_extended(std::vector<int> & masses);

    /**
     * @brief Computes the required fuel, acounting for 
     * mass and fuel mass
     * 
     * @param mass input mass
     * @return int fuel needed
     */
    int fuel_needed_total(int mass);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif
