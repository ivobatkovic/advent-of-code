#ifndef _INTCODE_H

#include<vector>

 /**
 * Function that computes the intcode for x
 *
 * @param values vector<int> x.
 * @return returns intcode at x[0].
 */
int intcode(std::vector<int> & x,int x0, int x1);
/**
 * Function that takes input a list x and modifies it at positions 
 * x[1]=x0, x[2]=x1, and then computes the intcode of x.
 *
 * @param values vector<int> x, int x0, int x1.
 * @return returns intcode at x[0]
 */
int solve_intcode(std::vector<int> & x,int x0, int x1);

/**
 * Function that takes input a list x and searches for value
 * x[1],x[2] to get output from the intcode program.
 *
 * @param values vector<int> x, int output
 * @return returns 100*x1+x2, where x1 and x2 are the found pairs.
 */
int solve_intcode_extended(std::vector<int> & x, int output);

#endif