#include "donut.hpp"
#include <set>
#include "utils.hpp"
#include <queue>
#include<iostream>

// Data structure for the queue
struct queue_data
{
  int m_depth;
  std::vector<int> m_pos;
  int m_level;

  queue_data(int n1, std::vector<int> n2, int n3) : 
      m_depth(n1), m_pos(n2), m_level(n3) {}

  bool operator<(const struct queue_data &other) const {
    return m_depth > other.m_depth;
  }
};

Donut::Donut(std::string file_name) : m_grid(), m_portals(), m_reach() {

  utils::readFile(file_name, m_grid);
  find_portals(m_portals,m_reach);
}

// Go through the entire grid and find the portals
void Donut::find_portals(portal_map &portals, reach_map &reach) {

  auto h = int(m_grid.size()), w = int(m_grid[0].size());

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {

      // Place holder for the position of portal
      int yp(0), xp(0);
      char key = m_grid[y][x];

      // Place holder for keypair
      std::string key_pair("");

      // If the key is an uppercase character, look around up,down,left,right
      if (isupper(key)) {
        if ( (y-2)>0 && isupper(m_grid[y-1][x]) && m_grid[y-2][x] == '.') {
          yp = y-2, xp = x;
          key_pair = std::string(1,m_grid[y - 1][x]) + std::string(1, key);
        } else if (y+2<h && isupper(m_grid[y+1][x]) && m_grid[y+2][x] == '.') {
          yp = y + 2, xp = x;
          key_pair = std::string(1, key) + std::string(1,m_grid[y + 1][x]);
        } else if (x-2>0 && isupper(m_grid[y][x-1]) && m_grid[y][x-2] == '.') {
          yp = y, xp = x-2;
          key_pair = std::string(1,m_grid[y][x - 1]) + std::string(1, key);
        } else if (x+2<w && isupper(m_grid[y][x+1]) && m_grid[y][x+2] == '.') {
          yp = y, xp = x+2;
          key_pair = std::string(1, key) + std::string(1,m_grid[y][x + 1]);
        }
      }
      // If we found a keypair include it
      if (key_pair.size() > 0) {
        portals[key_pair].push_back({yp,xp});
      }
    }
  }
  // Connect portals to each other
  for (auto &m : portals) {
    if (m.second.size() > 1) {
      auto v1 = m.second[0], v2 = m.second[1];
      std::vector<int> dir({1,-1});

      if (v1[0] == 2 || v1[0] == int(m_grid.size()-3) || 
          v1[1] == 2 || v1[1] == int(w-3)) {
        dir = std::vector<int>({-1,1});
      }
      reach[v1] = std::make_tuple(v2,dir[0],m.first);
      reach[v2] = std::make_tuple(v1, dir[1], m.first);
    }
  }
}

// Start at "AA" and try to get to "ZZ"
int Donut::shortest_path(bool level_check) {

  // Initial position, and desired final position
  auto pos = m_portals["AA"][0];
  auto goal = m_portals["ZZ"][0];

  std::vector<std::vector<int>> directions({{-1,0},{1,0},{0,1},{0,-1}});

  std::set<std::tuple<int,int,int>> visited;

  std::priority_queue<queue_data> q;
  q.push(queue_data(0, pos, 0));

  // Keep going until we end up at the goal
  while (!q.empty()) {

    // Pick "shortest" node
    auto q_ = q.top(); q.pop();

    // Check if we are at the goal (level_check for recursive part two)
    if (q_.m_pos == goal) {
      if (level_check) {
        if (q_.m_level == 0) {
          return q_.m_depth;
        }
      } else {
        return q_.m_depth;
      }
    }

    // Skip if we've been here before
    auto yp = q_.m_pos[0], xp = q_.m_pos[1];
    if (visited.count(std::make_tuple(yp,xp,q_.m_level))) {
      continue;
    }
    visited.insert(std::make_tuple(yp,xp,q_.m_level));

    // Check if we can teleport
    if (m_reach.count(std::vector<int>({yp,xp})) && q_.m_level >=0) {
      auto output = m_reach[std::vector<int>({yp, xp})];
      q.push(queue_data(
        q_.m_depth+1,std::get<0>(output), q_.m_level+std::get<1>(output)));
    }

    // Take a new step in the new direction 
    for (auto& dxdy : directions) {
      if (m_grid[yp+dxdy[0]][xp+dxdy[1]] == '.') {
        q.push(queue_data(
          q_.m_depth+1,std::vector<int>({yp+dxdy[0],xp+dxdy[1]}),q_.m_level));
      }
    }
  }
  // Failed
  return -1;
}
