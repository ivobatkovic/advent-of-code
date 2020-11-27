#include "beam.hpp"
#include <vector>

Beam::Beam(std::string file_name) : m_file_name(file_name), m_intcode() {
  m_intcode = Intcode(file_name, {}, true, false);
}

int Beam::part_one(int grid_size) {

  int nAsteroids(0);
  for (int x = 0; x < grid_size; x++) {
    for (int y = 0; y < grid_size; y++) {
      auto output = m_intcode({x,y});
      nAsteroids += std::get<1>(output);
    }
  }
  return nAsteroids;
}

int Beam::part_two(int square_size) {

  // Bottom left  corner
  std::vector<int64_t> bot_left({0,square_size-1});

  while (true) {
    // If bottom left corner has a detection
    if (std::get<1>(m_intcode(bot_left))) {
      // Check if top right has a detection - done
      auto top_right = std::vector<int64_t>({bot_left[0]+(square_size-1),
                                             bot_left[1] -(square_size-1)});
      if (std::get<1>(m_intcode(top_right))) {
        return bot_left[0]*10000 + top_right[1];
      // Otherwise move down
      } else {
        bot_left[1]++;
      }
    // Otherwise move to the right
    } else {
      bot_left[0]++;
    }
  }
}
