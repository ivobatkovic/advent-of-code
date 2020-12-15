#include "monitorstation.hpp"

#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_set>

#include "utils.hpp"

using std::string;
using std::vector;

MonitorStation::MonitorStation(string file_name) : m_input() {
  // Read the input
  m_input = utils::read_file(file_name);
}

vector<vector<size_t>> MonitorStation::find_asteroids(vector<string> grid) {
  // Loop through the grid and record the coordinates where an asteroid is
  vector<vector<size_t>> ids;
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == '#') {
        ids.push_back(vector<size_t>{i, j});
      }
    }
  }
  return ids;
}

int MonitorStation::find_closest(vector<vector<double>> asteroids) {
  // Input asteroids contains values of <distance,x,y>.
  int id = 0, min_val = 10000;
  for (size_t i = 0; i < asteroids.size(); i++) {
    // Find the index with smallest distance element
    if (asteroids[i][0] < min_val) {
      id = i;
      min_val = asteroids[i][0];
    }
  }
  return id;
}

std::tuple<int, int> MonitorStation::compute_vision(vector<string> grid) {
  // Get vector of <x,y> indices where asteroids are
  auto ids = find_asteroids(grid);

  vector<int> asteroids;

  // For each asteroid, look how many it can "see"
  for (auto &i : ids) {
    int row = i[0], col = i[1];
    std::unordered_set<float> monitor;
    // Loop through the list for all asteroids j != i
    for (auto &j : ids) {
      if (i != j) {
        // Compute the angle and store it
        int row1 = j[0], col1 = j[1];
        float angle = atan2(col1 - col, row1 - row);
        monitor.insert(angle);
      }
    }
    asteroids.push_back(int(monitor.size()));
  }

  // Find element, and index, with the most asteroids
  int max_asteroid = *std::max_element(asteroids.begin(), asteroids.end());
  int i_max_asteroid =
      std::max_element(asteroids.begin(), asteroids.end()) - asteroids.begin();

  return std::make_tuple(max_asteroid, i_max_asteroid);
}

int MonitorStation::blast(vector<string> grid, int asteroid_index, int number) {
  // Find positions of asteroids
  auto ids = find_asteroids(grid);

  // Use the "best" asteroid
  int x0 = ids[asteroid_index][0], y0 = ids[asteroid_index][1];
  ids.erase(ids.begin() + asteroid_index);

  // Keep track of all asteroids from the best one
  std::map<double, vector<vector<double>>> mp;
  for (auto &id : ids) {
    int dx = int(id[0]) - x0, dy = int(id[1]) - y0;
    double distance = sqrt(dx * dx + dy * dy), angle = atan2(dy, dx) - M_PI / 2;
    mp[angle].push_back(vector<double>{distance, double(id[0]), double(id[1])});
  }

  // Keep track of removed asteroids
  int n_removed = 0;

  // Check if there are atleast <number> asteroids left
  if (ids.size() >= std::size_t(number)) {
    while (true) {
      // Map keys go from -3/2pi -> 1/2pi. We go backwards through the map to go
      // clockwise
      for (auto iter = mp.rbegin(); iter != mp.rend(); iter++) {
        if (iter->second.size() > 0) {
          // Closest asteroid
          auto id = find_closest(iter->second);

          // Update n-th asteroid destroyed
          int xx = iter->second[id][1];
          int yy = iter->second[id][2];
          n_removed += 1;

          if (n_removed == number) {
            return yy * 100 + xx;
          }

          // Remove the asteroid from the map
          iter->second.erase(iter->second.begin() + id);
        }
      }
    }
    // Otherwise no solution
  } else {
    return -1;
  }
}