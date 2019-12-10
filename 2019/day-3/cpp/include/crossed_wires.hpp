#ifndef _CROSSED_WIRES_H_

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>

class CrossedWires {

public:
  std::vector<std::vector<std::string>> wire;
  int manhattan_distance;
  int n_steps;

  /**
  * Constructor
  *
  * @param values string file name.
  */
  CrossedWires(std::string fileName);

  /**
  * Given the instructions in wires, the function returns an (N+1)x4 array
  of wire positions. First two elements are the x,y positions, the third
  element is the cummulated wire length, and the fourth element indicates if
  the line is vertical or horizontal.
  * @param values vector<vector<string> & input, int &  dist, int & step
  */
  void crossed_wires(std::vector<std::vector<std::string>> & input, int & dist,
    int & step);

  /**
  * This function assumes that the wires aren't routed along eachother,
  * i.e., they will only cross perpendicularly, hence it is enough only to check
  * vertical wire segments vs horizontal wire segments.
  * @param values & input, & dist, & step
  */
  void compute_wire_segments(std::vector<std::vector<std::string>> & wires,
    std::vector<std::vector<int>> wire_segments[2]);

  /**
  * Loop through the wire segments wire1 and wire2 and looks for possible
  intersections.
  * @param values wire1, wire2
  * returns distance and steps
  */
  void intersect_wires(std::vector<std::vector<int>> & wire1,
    std::vector<std::vector<int>> & wire2, std::vector<int> & dist,
    std::vector<int> & steps);

  /**
  * Checks if line1: [A,B] intersects with line2: [C,D]. Assumes only
  horizontal and vertical lines.
  * @param values vector<int> A,B,C,D,point,int steps
  * returns intersection point and steps.
  */
  bool intersect(std::vector<int> & A, std::vector<int> & B,
    std::vector<int> & C, std::vector<int> & D,std::vector<int> & point,
    int & steps);

  /**
  * Read file from fileName and store it in output
  * @param values string fileName, vector<vector<string>> output
  */
  bool readFile(std::string fileName,
    std::vector<std::vector<std::string>> & output);




};

#endif
