#ifndef _FUEL_COUNTER_H

#include<vector>

 /**
 * Function that computes the fuel needed for the input masses
 *
 * @param values Scalar or vector of masses.
 * @return returns total fuel needed.
 */
int fuel_counter(std::vector<int> & masses);
/**
 * Function that computes the fuel needed for the input masses
 *
 * @param values Scalar mass.
 * @return returns total fuel needed.
 */
int fuel_counter(int mass);


/**
 * Function that computes the fuel needed for the input masses and the
 * extra fuel needed for the new fuel itself.
 *
 * @param values Scalar or vector of masses.
 * @return returns total fuel needed.
 */
int fuel_counter_extended(std::vector<int> & masses);

/**
 * Function that computes the fuel needed for the mass and its own
 * fuel.
 *
 * @param values Scalar mass.
 * @return returns total fuel needed.
 */
int fuel_needed_total(int mass);

#endif