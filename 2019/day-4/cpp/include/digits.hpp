#ifndef _DIGITS_H_

#include<string>

class Digits {

public:

  /**
  * Constructor
  *
  * @param values string file name.
  */
  Digits();

  /**
  * Given the instructions in wires, the function returns an (N+1)x4 array
  of wire positions. First two elements are the x,y positions, the third
  element is the cummulated wire length, and the fourth element indicates if
  the line is vertical or horizontal.
  * @param values vector<vector<string> & input, int &  dist, int & step
  */
  static bool double_digit(std::string num);

  /**
  * This function assumes that the wires aren't routed along eachother,
  * i.e., they will only cross perpendicularly, hence it is enough only to check
  * vertical wire segments vs horizontal wire segments.
  * @param values & input, & dist, & step
  */
  static bool double_digit_no_adjacent(std::string num);

  /**
  * Loop through the wire segments wire1 and wire2 and looks for possible
  intersections.
  * @param values wire1, wire2
  * returns distance and steps
  */
  static std::string make_monotonic(std::string start);

  /**
  * Checks if line1: [A,B] intersects with line2: [C,D]. Assumes only
  horizontal and vertical lines.
  * @param values vector<int> A,B,C,D,point,int steps
  * returns intersection point and steps.
  */
  static std::string next_monotonic(std::string num);


};

#endif
