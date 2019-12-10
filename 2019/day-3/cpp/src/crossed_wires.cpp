#include "crossed_wires.hpp"

using std::vector;
using std::string;

CrossedWires::CrossedWires(string fileName) : wire{}, manhattan_distance{0}, n_steps{0} {
    if(readFile(fileName,wire)){
      crossed_wires(wire,manhattan_distance,n_steps);
    }
}

void CrossedWires::crossed_wires(vector<vector<string>> & input, int & dist, int & step) {

  vector<vector<int>> wire_segments[2];
  compute_wire_segments(input,wire_segments);

  vector<int> points;
  vector<int> steps;
  intersect_wires(wire_segments[0],wire_segments[1],points,steps);
  dist = *std::min_element(points.begin(),points.end());
  step = *std::min_element(steps.begin(),steps.end());

}

void CrossedWires::compute_wire_segments(vector<vector<string>> & wires,vector<vector<int>> wire_segments[2]) {

  for (unsigned int i = 0; i < wires.size(); i++) {
    vector<int> pos {0, 0, 0, 0};
    vector<vector<int>> wire_segment; wire_segment.push_back(pos);

    for (unsigned int j = 0; j < wires[i].size(); j++) {
      string w = wires[i][j];
      int dx = 0, dy = 0, orientation = 0;
      int step = std::stoi(w.substr(1,w.back()));

      if (w[0] == 'L' || w[0] == 'R')
        dx = (w[0] == 'R') ? step : -step;
      else if (w[0] == 'U' || w[0] == 'D') {
        dy = (w[0] == 'U') ? step : -step;
        orientation = 1;
      }
      pos[0]+=dx, pos[1]+=dy, pos[2]+= step, pos[3]=orientation;
      wire_segment.push_back(pos);
    }
    wire_segments[i] = wire_segment;
  }
}

void CrossedWires::intersect_wires(vector<vector<int>> & wire1,vector<vector<int>> & wire2, vector<int> & dist, vector<int> & steps) {

  for (unsigned int i = 0; i < wire1.size()-1; i++){
    for (unsigned int j = 0; j <wire2.size()-1; j++) {
      vector<int> point; int st;
      if(intersect(wire1[i],wire1[i+1],wire2[j],wire2[j+1],point,st)){
        dist.push_back(std::abs(point[0])+std::abs(point[1]));
        steps.push_back(st);
      }
    }
  }
}

bool CrossedWires::intersect(vector<int> & A, vector<int> & B,vector<int> & C, vector<int> & D,vector<int> & point,int  & steps) {


  if (B[3]==D[3]){
    return false;
  }
  int x1min = std::min(A[0],B[0]), x1max = std::max(A[0],B[0]);
  int y1min = std::min(A[1],B[1]), y1max = std::max(A[1],B[1]);

  int x2min = std::min(C[0],D[0]), x2max = std::max(C[0],D[0]);
  int y2min = std::min(C[1],D[1]), y2max = std::max(C[1],D[1]);

  if ((x1max >= x2min) && (x1min <= x2max) && (y1max >= y2min) && (y1min <= y2max)){
    // Compute intersection point
    point = ((x1max-x1min) != 0) ? vector<int>{x2min,y1min} : vector<int>{x1min,y2min};
    int wire_steps = A[2] + C[2];

    int steps_to_point = std::abs(A[0]-point[0]) + std::abs(A[1]-point[1]) +
                        std::abs(C[0]-point[0]) + std::abs(C[1]-point[1]);
    steps = wire_steps+steps_to_point;

    return true;
  }
  return false;
}

bool CrossedWires::readFile(string fileName, vector<vector<string>> & output) {
  std::ifstream file(fileName);
  if(!file) {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    return false;
  }
  std::string row, instruction;
  while(std::getline(file,row)) {
    std::stringstream ss(row);
    std::vector<std::string> results;
    while (ss.good()) {
      getline(ss,instruction,',');
      results.push_back(instruction);
    }
    output.push_back(results);
  }
  file.close();
  return true;
}
