#include "2020/day24/cpp/include/day24.hpp"

#include <regex>
#include <unordered_map>

#include "utils/cpp/include/utils.hpp"
using day24::input_type;
using day24::output_type;
using day24::set_type;
using day24::vector_type;

template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
  return {l.first + r.first, l.second + r.second};
}

input_type day24::transform_input(std::vector<std::string> &input) {
  std::regex rgx("(ne|se|nw|sw|e|w)");

  input_type output;
  for (auto &inp : input) {
    std::smatch sm;
    std::vector<std::string> instructions;
    while (std::regex_search(inp, sm, rgx)) {
      instructions.push_back(sm[0]);
      inp = sm.suffix().str();
    }
    output.push_back(instructions);
  }
  return output;
}

input_type day24::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

set_type day24::traverse(const input_type &input_) {
  // Directions to move in the hex grid
  std::unordered_map<std::string, std::pair<int, float>> dir(
      {{"e", {0, 1}},
       {"w", {0, -1}},
       {"se", {1, 0.5}},
       {"sw", {1, -0.5}},
       {"ne", {-1, 0.5}},
       {"nw", {-1, -0.5}}});

  // Keep track of flipped (black) positions
  set_type tiles;
  for (auto &instructions : input_) {
    // Follow instructions from (0,0)
    std::pair<int, float> pos({0, 0});
    for (auto &instruction : instructions) {
      pos = pos + dir[instruction];
    }
    // If the tile is black -> turn it white
    if (tiles.count(pos)) {
      tiles.erase(pos);
      // If the tile is white -> turn it black
    } else {
      tiles.insert(pos);
    }
  }
  return tiles;
}

// Implement part one solution
output_type day24::solve_part1(const input_type &input_) {
  return traverse(input_).size();
}

set_type day24::get_active(set_type &tile, vector_type &neighbors) {
  // Consider all black tiles and their neighbors
  set_type active_tile;
  for (auto &pos : tile) {
    active_tile.insert(pos);
    for (auto &dxdy : neighbors) {
      active_tile.insert(pos + dxdy);
    }
  }
  return active_tile;
}

// Implement part two solution
output_type day24::solve_part2(const input_type &input_) {
  auto tile = traverse(input_);
  vector_type neighbors(
      {{0, 1}, {0, -1}, {1, 0.5}, {1, -0.5}, {-1, 0.5}, {-1, -0.5}});

  // Update the tiles n times
  for (int i = 0; i < 100; i++) {
    // Get all potential tiles that can flip
    auto potential_tiles = get_active(tile, neighbors);

    // Keep track of black tiles
    set_type update;
    for (auto &pos : potential_tiles) {
      // Check how many black neighbors the tile has
      int count = 0;
      for (auto &neighbor : neighbors) {
        count += (tile.count(pos + neighbor)) ? 1 : 0;
      }
      // Decide to flip or not
      if (!tile.count(pos) && count == 2) {
        update.insert(pos);
      } else if (tile.count(pos) && count != 0 && count <= 2) {
        update.insert(pos);
      }
    }
    tile = update;
  }
  return tile.size();
}
