#include "day17.hpp"

#include <algorithm>

#include "utils.hpp"

using day17::input_type;
using day17::output_type;
using day17::set_type;

input_type day17::transform_input(std::vector<std::string> &input) {
  return input;
}

input_type day17::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

set_type day17::get_potential_pos(set_type active, set_type dirs) {
  set_type potential_pos;
  // For each active position, include its neighbors
  for (auto &active_pos : active) {
    for (auto &dir_pos : dirs) {
      std::array<int, 4> pos;
      std::transform(active_pos.begin(), active_pos.end(), dir_pos.begin(),
                     pos.begin(), std::plus<int>());
      potential_pos.insert(pos);
    }
  }
  return potential_pos;
}

int day17::simulate(input_type input, int ndim) {
  // Create a set of directions that spans x-y-z-w-plane
  std::vector<std::vector<int>> directions(ndim, {-1, 0, 1});
  for (int i = 0; i < 4 - ndim; i++) {
    directions.push_back({0});
  }

  set_type dirs;
  for (auto &x : directions[0]) {
    for (auto &y : directions[1]) {
      for (auto &z : directions[2]) {
        for (auto &w : directions[3]) {
          dirs.insert(std::array<int, 4>({{x, y, z, w}}));
        }
      }
    }
  }
  // Remove origin
  dirs.erase(std::array<int, 4>({{0, 0, 0, 0}}));

  // Keep track of active positions
  set_type active;
  for (int row = 0; row < int(input.size()); row++) {
    for (int col = 0; col < int(input[0].size()); col++) {
      if (input[row][col] == '#') {
        active.insert(std::array<int, 4>({{row, col, 0, 0}}));
      }
    }
  }

  // Apply cycle 6 times
  for (auto cycle = 0; cycle < 6; cycle++) {
    // Keep track of cells that are activated
    set_type updated;

    // Find potential cells that might be activated
    auto potential_pos = get_potential_pos(active, dirs);

    // Go through all potential cells
    for (auto &pos : potential_pos) {
      auto &[x, y, z, w] = pos;
      int count(0);
      // Search directions
      for (auto &[dx, dy, dz, dw] : dirs) {
        count += (active.count(
                     std::array<int, 4>({{x + dx, y + dy, z + dz, w + dw}})))
                     ? 1
                     : 0;
      }
      if (active.count(pos) && (count == 2 || count == 3)) {
        updated.insert(pos);
      } else if (!active.count(pos) && count == 3) {
        updated.insert(pos);
      }
    }
    active = updated;
  }

  return active.size();
}

// Implement part one solution
output_type day17::solve_part1(const input_type &input_) {
  return simulate(input_, 3);
}

// Implement part two solution
output_type day17::solve_part2(const input_type &input_) {
  return simulate(input_, 4);
}
