#include "wires.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>

using std::vector;
using std::string;

Wires::Wires() : m_wire{}, m_distance{0}, m_steps{0} {}

Wires::Wires(string file_name) : m_wire{}, m_distance{0}, m_steps{0} {

  // Read input file contents into wire
  utils::readCSVFile(file_name,m_wire);
  
}

void Wires::solve() {
  // Generate wire segments
  vector<vector<int>> wire_segments[2];
  compute_wire_segments(wire_segments);

  // Intersect the wires and update distance and steps member variables
  intersect_wires(wire_segments[0], wire_segments[1]);
}

void Wires::compute_wire_segments(vector<vector<int>> wire_segments[2])
{

  // Loop over each wire part
  for (std::size_t i = 0; i < 2; i++)
  {
    // Initial position
    vector<int> pos {0, 0, 0, 0};
    vector<vector<int>> wire_segment{pos};

    // Loop over each segment in the wire

    for (auto &segments : m_wire[i])
    {
      auto seg = segments;

      //Default directions
      int dx = 0, dy = 0, orientation = 0;
      // Obtain the numeric part of the string
      int step = std::stoi(seg.substr(1, seg.back()));

      if (seg[0] == 'L' || seg[0] == 'R') {
        dx = (seg[0] == 'R') ? step : -step;
      }
      else if (seg[0] == 'U' || seg[0] == 'D') {
        dy = (seg[0] == 'U') ? step : -step;
        orientation = 1;
      }

      // Update position, step length, and orientation
      pos[0]+=dx, pos[1]+=dy, pos[2]+= step, pos[3]=orientation;
      wire_segment.push_back(pos);
    }

    wire_segments[i] = wire_segment;
  }
}

void Wires::intersect_wires(vector<vector<int>> & wire1, 
                            vector<vector<int>> & wire2) {

  // Place holders for manhattan distances and taken steps for each intersection
  vector<int> distances, taken_steps;

  // Intersect each wire segment with another
  for (std::size_t i = 1; i < wire1.size()-1; i++){
    for (std::size_t j = 1; j <wire2.size()-1; j++) {
      // Obtain intersection point and steps taken
      vector<int> point; int steps;

      // Intersect wire parts, e.g., the lines [A B] with [C D]
      if (intersect(wire1[i], wire1[i+1], wire2[j], wire2[j+1], point, steps))
      {
        // Store the distances and steps to the intersection
        distances.push_back(std::abs(point[0]) + std::abs(point[1]));
        taken_steps.push_back(steps);
      }
    }
  }
  m_distance = *std::min_element(distances.begin(), distances.end());
  m_steps = *std::min_element(taken_steps.begin(), taken_steps.end());
}

// Lines consist of [A B] and [C D], where A,B,C, and D are 2-dim.
bool Wires::intersect(vector<int> &A, vector<int> &B, 
                      vector<int> &C, vector<int> &D, 
                      vector<int> &point_, int &steps_)
{
  // Check if lines are parallel
  if (B[3]==D[3]){
    return false;
  }

  // Perform intersection
  int x1min = std::min(A[0],B[0]), x1max = std::max(A[0],B[0]);
  int y1min = std::min(A[1],B[1]), y1max = std::max(A[1],B[1]);

  int x2min = std::min(C[0],D[0]), x2max = std::max(C[0],D[0]);
  int y2min = std::min(C[1],D[1]), y2max = std::max(C[1],D[1]);

  // Since we always compare perpendicular lines check if they overlap
  if ((x1max >= x2min) && (x1min <= x2max) && 
      (y1max >= y2min) && (y1min <= y2max)){
    point_ = ((x1max-x1min) != 0) ? 
      vector<int>{x2min,y1min} : vector<int>{x1min,y2min};
      
    int wire_steps = A[2] + C[2];

    int steps_to_point = std::abs(A[0]-point_[0]) + std::abs(A[1]-point_[1]) +
                        std::abs(C[0]-point_[0]) + std::abs(C[1]-point_[1]);
    steps_ = wire_steps+steps_to_point;

    return true;
  }
  return false;
}
