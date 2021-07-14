#include "2020/day20/cpp/include/day20.hpp"

#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "2020/day20/cpp/include/jiggsaw.hpp"
#include "utils/cpp/include/utils.hpp"
using day20::input_type;
using day20::output_type;

input_type day20::transform_input(std::vector<std::string> &input) {
  input_type image;
  std::string tile_nr;

  // Go through each line
  for (auto &inp : input) {
    // Skip empty line
    if (inp.length() == 0) {
      continue;
    }
    // Check for tile number
    if (inp[0] == 'T') {
      tile_nr = inp.substr(5, inp.length() - 6);
      // If no tile number, append the row to the current tile
    } else {
      image[tile_nr].push_back(inp);
    }
  }

  return image;
}

input_type day20::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day20::solve_part1(const input_type &input_) {
  // Feed the Jiggsaw class all image pieces
  Jiggsaw j(input_);
  j.solve();

  uint64_t prod(1);
  for (auto &key : j.get_corners()) {
    prod *= std::stoll(j.m_complete_images[key].first);
  }
  return prod;
}

// Implement part two solution
output_type day20::solve_part2(const input_type &input_) {
  // Feed the Jiggsaw class all image pieces
  Jiggsaw j(input_);
  j.solve();

  std::vector<std::string> monster(
      {"                  # ", "#    ##    ##    ###", " #  #  #  #  #  #   "});
  return j.get_rough_waters(monster);
}
