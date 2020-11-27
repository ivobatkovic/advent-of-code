#include "paint.hpp"

#include <math.h>
#include <vector>
#include <tuple>
#include <iostream>

Paint::Paint() {}

int Paint::get_painted_tiles(pairmap &map, Intcode &intcode)
{

  // Initialize starting pose
  int px(0), py(0);
  auto dir = M_PI_2;

  pairmap painted_tiles;
  
  bool terminated = false;
  while (!terminated) {
    
    std::pair<int, int> pxpy(px, py);

    if (!map.count(pxpy)) {
      map[pxpy] = ".";
    }  
    int input = (map[pxpy] == ".") ? 0 : 1;

    auto output1 = intcode(input);
    auto output2 = intcode();
    
    bool cond1 = std::get<0>(output1);
    int paint = std::get<1>(output1);

    bool cond2 = std::get<0>(output2);
    int turn = std::get<1>(output2);

    
    dir += (turn == 0) ? M_PI_2 : -M_PI_2;
    std::string color = (paint==1) ? "#" : ".";

    if (map[pxpy] != color) {
      painted_tiles[pxpy] = 1;
      map[pxpy] = color;
    }

    py = py+int(cos(dir));
    px = px-int(sin(dir));

    terminated = (cond1 || cond2);
   
  }
  
  return painted_tiles.size();
}


void Paint::paint_map(pairmap map) {

  int min_x(WINT_MAX), max_x(WINT_MIN);
  int min_y(WINT_MAX), max_y(WINT_MIN);

  for (auto &m : map) {
    min_x = (min_x > m.first.first) ? m.first.first : min_x;
    min_y = (min_y > m.first.second) ? m.first.second : min_y;

    max_x = (max_x < m.first.first) ? m.first.first : max_x;
    max_y = (max_y < m.first.second) ? m.first.second : max_y;
  }
  for (int row = min_x; row < max_x+1; row++) {
    std::string str = "";
    for (int col = min_y; col < max_y+1;col++) {
      str += (map[std::pair<int,int>(row,col)] == "#") ? "X" : " ";
    }
    std::cout << str << std::endl;
  }

}