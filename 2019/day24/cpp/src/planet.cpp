#include "planet.hpp"

#include <math.h>

#include <algorithm>

#include "utils.hpp"

Planet::Planet(std::string file_name, bool recursive)
    : m_empty_grid(),
      m_grid(),
      m_h(),
      m_w(),
      m_recursive(recursive),
      m_neighbors_map(),
      m_map_config() {
  // Initialize empty grid and read the map (input)
  m_empty_grid = std::vector<std::string>(5, {"....."});
  m_grid = read_map(file_name);

  // Get width and height of grid
  m_h = m_grid[0].data.size();
  m_w = m_grid[0].data[0].size();

  compute_neighbors();
}

std::map<int, grid_struct> Planet::read_map(std::string file_name) {
  auto input = utils::read_file(file_name);
  std::map<int, grid_struct> grid;
  grid[0] = grid_struct(input);

  return grid;
}

// Make a mapping of how neighbors are connected (look at README)
void Planet::compute_neighbors() {
  std::vector<std::vector<int>> directions({{-1, 0}, {1, 0}, {0, 1}, {0, -1}});

  // Mid point treated differently depending on recursive setting
  int mid_y = m_h / 2;
  int mid_x = m_w / 2;

  for (int row = 0; row < m_h; row++) {
    for (int col = 0; col < m_w; col++) {
      std::vector<std::vector<int>> neighbors;
      for (auto &d : directions) {
        int dx = d[0], dy = d[1];
        auto row_ = row + dy, col_ = col + dx;

        if (row_ < 0 && m_recursive) {
          neighbors.push_back({-1, mid_y - 1, mid_x});
        } else if (row_ >= m_h && m_recursive) {
          neighbors.push_back({-1, mid_y + 1, mid_x});
        } else if (col_ < 0 && m_recursive) {
          neighbors.push_back({-1, mid_y, mid_x - 1});
        } else if (col_ >= m_h && m_recursive) {
          neighbors.push_back({-1, mid_y, mid_x + 1});
        } else if (col_ == mid_x && row_ == mid_y && m_recursive) {
          if (dx == 1) {
            for (int y = 0; y < m_h; y++) {
              neighbors.push_back({1, y, 0});
            }
          } else if (dx == -1) {
            for (int y = 0; y < m_h; y++) {
              neighbors.push_back({1, y, m_w - 1});
            }
          } else if (dy == 1) {
            for (int x = 0; x < m_w; x++) {
              neighbors.push_back({1, 0, x});
            }
          } else if (dy == -1) {
            for (int x = 0; x < m_w; x++) {
              neighbors.push_back({1, m_h - 1, x});
            }
          }
        } else if (col_ >= 0 && col_ < m_w && row_ >= 0 && row_ < m_h) {
          neighbors.push_back({0, row_, col_});
        }
      }
      m_neighbors_map[std::make_pair(row, col)] = neighbors;
    }
  }
}

// Perform the updates of the planet
bool Planet::update(int n_updates) {
  // Initialize recursive levels
  int min_level, max_level;
  if (m_recursive) {
    min_level = int(floor(-n_updates / 2));
    max_level = int(ceil(n_updates / 2) + 1);
    for (int level = min_level; level < max_level; level++) {
      m_grid[level];
    }
  }

  // Loop through updates
  for (int u = 0; u < n_updates; u++) {
    std::map<int, grid_struct> temp_level;

    int depth = u / 2;

    for (int level = -depth - 1; level < depth + 2; level++) {
      std::vector<std::string> temp_grid;

      for (int row = 0; row < m_h; row++) {
        std::string new_row("");
        for (int col = 0; col < m_w; col++) {
          // Add all neighbors in a string
          std::string nbors = "";
          for (auto &level_y_x : m_neighbors_map[std::make_pair(row, col)]) {
            auto level_dir = level_y_x[0];
            auto y = level_y_x[1];
            auto x = level_y_x[2];
            nbors += m_grid[level + level_dir].data[y][x];
          }

          // See how many neighbors are present ( number of '#') and update
          size_t n_neighbors = std::count(nbors.begin(), nbors.end(), '#');
          if (m_grid[level].data[row][col] == '#') {
            if (n_neighbors == 1) {
              new_row += '#';
            } else {
              new_row += '.';
            }
          } else {
            if (n_neighbors == 1 || n_neighbors == 2) {
              new_row += '#';
            } else {
              new_row += '.';
            }
          }
        }
        // Update the temporary grid
        temp_grid.push_back(new_row);
      }
      // Update the temporary level
      temp_level[level] = temp_grid;
    }
    // Update grid after the update step
    m_grid = temp_level;

    // For part one, check if level=0 is repeated
    if (!m_recursive) {
      std::string str;
      for (auto &x : m_grid[0].data) {
        str += x;
      }
      if (m_map_config.count(str)) {
        return true;
      } else {
        m_map_config.insert(str);
      }
    }
  }
  return false;
}

// Solve part one: update the system until it is repeated
int Planet::part_one() {
  int iter(0);
  while (true) {
    // If sequence is repeated compute the metric
    if (update()) {
      std::string strng;
      for (auto &x : m_grid[0].data) {
        strng += x;
      }
      int sm(0);
      for (size_t i = 0; i < strng.size(); i++) {
        sm += (strng[i] == '#') ? pow(2, i) : 0;
      }
      return sm;
    }
    iter++;
  }
}

// Solve part two: Update the system n_steps times and count how many #
// across all layers
int Planet::part_two(int n_steps) {
  update(n_steps);
  size_t bugs = 0;
  for (auto &level : m_grid) {
    for (auto &row : level.second.data) {
      bugs += std::count(row.begin(), row.end(), '#');
    }
    if (level.second.data[m_h / 2][m_w / 2] == '#') {
      bugs--;
    }
  }
  return bugs;
}
