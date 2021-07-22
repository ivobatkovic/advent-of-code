#include "2020/day20/cpp/include/jiggsaw.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

Jiggsaw::Jiggsaw(const images_type &images)
    : m_images(images),
      m_image_sides(compute_image_sides()),
      m_complete_images(),
      m_combined_image(),
      m_xmin(0),
      m_ymin(0),
      m_xmax(0),
      m_ymax(0) {}

Jiggsaw::images_type Jiggsaw::compute_image_sides() {
  image_sides_type sides;
  // Go through each image and compute the right, top, left, bottom sides
  for (auto &image : m_images) {
    for (int i = 0; i < 4; i++) {
      sides[image.first].push_back(get_side(image.first, i));
    }
  }
  return sides;
}

std::string Jiggsaw::get_side(std::string tile, int dir) {
  std::string side;
  // Return top side
  if (dir == 1) {
    return m_images[tile].front();
    // Return bottom side
  } else if (dir == 3) {
    return m_images[tile].back();
    // Return right side
  } else if (dir == 0) {
    for (auto &row : m_images[tile]) {
      side += row.back();
    }
    return side;
    // Return left side
  } else {
    for (auto &row : m_images[tile]) {
      side += row.front();
    }
    return side;
  }
}

void Jiggsaw::rotate(image_type &tile, int n_times) {
  // Rotate an image 90 degrees counter-clockwise n_times
  for (int i = 0; i < n_times; i++) {
    int N = tile.size();
    for (int x = 0; x < N / 2; x++) {
      for (int y = x; y < N - x - 1; y++) {
        int temp = tile[x][y];
        tile[x][y] = tile[y][N - 1 - x];
        tile[y][N - 1 - x] = tile[N - 1 - x][N - 1 - y];
        tile[N - 1 - x][N - 1 - y] = tile[N - 1 - y][x];
        tile[N - 1 - y][x] = temp;
      }
    }
  }
}

void Jiggsaw::reverse(image_type &tile) {
  // Flip image up-side-down
  std::reverse(tile.begin(), tile.end());
}

void Jiggsaw::flip(image_type &tile) {
  // Flip image left-to-right
  for (auto &row : tile) {
    std::reverse(row.begin(), row.end());
  }
}

void Jiggsaw::organize_tile(std::string tile, int dir_to, int dir_from) {
  // Transform the neighboring map to match the connection
  if (dir_to == dir_from) {
    if (dir_to == 1 || dir_to == 3) {
      reverse(m_images[tile]);
    } else {
      flip(m_images[tile]);
    }
  } else if ((dir_to + dir_from) == 3 && (dir_from == 3 || dir_from == 1)) {
    rotate(m_images[tile], 3);
  } else if ((dir_to + dir_from) == 3 && (dir_from == 0 || dir_from == 2)) {
    rotate(m_images[tile], 1);
  } else if ((dir_to + dir_from) == 5 || (dir_to + dir_from) == 1) {
    rotate(m_images[tile], 1);
    reverse(m_images[tile]);
  }

  // Update new image sides
  for (int i = 0; i < 4; i++) {
    m_image_sides[tile][i] = get_side(tile, i);
  }
}

bool Jiggsaw::find_matching_tile(std::string current, std::string tile,
                                 int dir_to) {
  // Find a tile that matches the current side
  auto current_side = m_image_sides[current][dir_to];

  // Go through all four sides of the tile
  for (int i = 0; i < 4; i++) {
    auto tile_side = m_image_sides[tile][i];

    // Check if current side matches the tile side
    bool forward_match = (current_side == tile_side);

    // Check if the current side matches the tile side in reverse
    std::reverse(tile_side.begin(), tile_side.end());
    if (current_side == tile_side) {
      forward_match = true;
      // Apply transformation to fix the tile
      if (i % 2 == 0) {
        reverse(m_images[tile]);
      } else {
        flip(m_images[tile]);
      }
    }
    // If we found a matchign tile, organize it properly to fit the map
    if (forward_match) {
      organize_tile(tile, dir_to, i);
      return true;
    }
  }
  return false;
}

void Jiggsaw::solve() {
  // Start from any (first) key in the input
  std::string start = std::begin(m_image_sides)->first;
  std::unordered_set<std::string> visited, decided;
  decided.insert(start);

  // Store the complete image of tiles
  m_complete_images.clear();
  m_complete_images[{0, 0}] =
      std::pair<std::string, image_type>({start, m_images[start]});

  // Queue to go through all tiles
  std::queue<std::tuple<std::string, int, int>> q;
  q.push(std::tuple<std::string, int, int>({start, 0, 0}));

  while (!q.empty()) {
    // Get next in queue
    auto [current, y, x] = q.front();
    q.pop();
    if (visited.count(current)) {
      continue;
    }
    visited.insert(current);

    // Check the tiles
    for (auto &image_side : m_image_sides) {
      auto tile = image_side.first;
      if (visited.count(tile) || current == tile || decided.count(tile)) {
        continue;
      }
      // Check all our "directions" with the other ones
      for (int dir = 0; dir < 4; dir++) {
        if (find_matching_tile(current, tile, dir)) {
          // Set direction to assign the tile
          int dx = (dir == 0) ? 1 : (dir == 2) ? -1 : 0;
          int dy = (dir == 1) ? 1 : (dir == 3) ? -1 : 0;

          // Update grid size
          m_xmin = (m_xmin > x + dx) ? x + dx : m_xmin;
          m_ymin = (m_ymin > y + dy) ? y + dy : m_ymin;
          m_xmax = (m_xmax < x + dx) ? x + dx : m_xmax;
          m_ymax = (m_ymax < y + dy) ? y + dy : m_ymax;

          // Update the complete image
          m_complete_images[{y + dy, x + dx}] =
              std::pair<std::string, image_type>({tile, m_images[tile]});

          // Add tile to queue
          q.push(std::tuple<std::string, int, int>({tile, y + dy, x + dx}));
          decided.insert(tile);
          break;
        }
      }
    }
  }
  // Flip the image upside down to match the directions
  for (auto &image : m_complete_images) {
    reverse(image.second.second);
  }
  // Combine the complete images into a big image
  combine_images();
}

void Jiggsaw::combine_images() {
  m_combined_image.clear();
  int n_rows = m_complete_images[{0, 0}].second.size();

  // Go through each connected of tiles
  for (int y = m_ymin; y < m_ymax + 1; y++) {
    // For each tile, go through its rows
    for (int row = 1; row < n_rows - 1; row++) {
      std::string row_;
      // Go through each row-tile
      for (int x = m_xmin; x < m_xmax + 1; x++) {
        std::string image_row = m_complete_images[{y, x}].second[row];
        row_ += image_row.substr(1, image_row.size() - 2);
      }
      m_combined_image.push_back(row_);
    }
  }
}

std::vector<std::pair<int, int>> Jiggsaw::get_corners() {
  // Return corner tiles
  return {
      {m_ymin, m_xmin}, {m_ymax, m_xmin}, {m_ymin, m_xmax}, {m_ymax, m_xmax}};
}

int Jiggsaw::find_monsters(image_type &monster) {
  // Image height and width
  int h = m_combined_image.size();
  int w = m_combined_image[0].size();

  // Monster height and width
  int h_monster = monster.size();
  int w_monster = monster[0].size();

  // Keep track of rotations
  int op = 1;

  // Go through combinations
  auto &img = m_combined_image;
  for (int combination = 0; combination < 8; combination++) {
    int n_monsters = 0;

    // Go through a mask of monster height and width size
    for (int row = 0; row < h - h_monster; row++) {
      for (int col = 0; col < w - w_monster; col++) {
        bool found = true;
        // Go through the monster sub-mask
        for (auto i = 0; i < h_monster; i++) {
          bool braked = false;
          for (auto j = 0; j < w_monster; j++) {
            // If monster and image don't overlap: break
            if (monster[i][j] == '#' && img[row + i][col + j] != '#') {
              found = false;
              braked = true;
              break;
            }
          }
          if (braked) {
            break;
          }
        }
        if (found) {
          n_monsters++;
        }
      }
    }

    if (n_monsters > 0) {
      return n_monsters;
    }
    // Reverse image
    if (op == 1) {
      reverse(m_combined_image);
      // If no match, reverse back and rotate
    } else {
      reverse(m_combined_image);
      rotate(m_combined_image, 1);
    }
    op *= -1;
  }
  return 0;
}
int Jiggsaw::get_rough_waters(image_type &monster) {
  // Get number of monsters
  auto nr_monsters = find_monsters(monster);

  // Check how many '#' the monster has
  int size_monster(0);
  for (auto &row : monster) {
    for (auto &elem : row) {
      size_monster += (elem == '#') ? 1 : 0;
    }
  }
  // Check how many '#' the image has
  int rough_waters(0);
  for (auto &row : m_combined_image) {
    for (auto &elem : row) {
      rough_waters += (elem == '#') ? 1 : 0;
    }
  }

  return rough_waters - nr_monsters * size_monster;
}
