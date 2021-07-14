#include "2020/day11/cpp/include/day11.hpp"

#include <algorithm>
#include <map>

#include "utils/cpp/include/utils.hpp"
using day11::input_type;
using day11::output_type;

using neighbor_map =
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>;
using positions = std::vector<std::pair<int, int>>;

positions get_seat_positions(const input_type &input);
positions get_neighbor_directions();
int update_seats(const input_type &input_, positions &seat_positions,
                 neighbor_map &neighbors, int adjacent_seats);
neighbor_map get_neighbors_part1(const input_type &input,
                                 positions &seat_position);
neighbor_map get_neighbors_part2(const input_type &input,
                                 positions &seat_position);

input_type day11::transform_input(std::vector<std::string> &input) {
  // Pad the input data so that we can traverse the grid easier later
  input_type output(1, std::string(input[0].size() + 2, 'X'));
  for (auto &inp : input) {
    output.push_back("X" + inp + "X");
  }
  output.push_back(std::string(input[0].size() + 2, 'X'));
  return output;
}

input_type day11::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

positions get_seat_positions(const input_type &input) {
  // Return positions <row,col> for all empty seats
  positions output;
  for (size_t row = 0; row < input.size(); row++) {
    for (size_t col = 0; col < input[0].size(); col++) {
      if (input[row][col] == 'L') {
        output.push_back({row, col});
      }
    }
  }
  return output;
}

positions get_neighbor_directions() {
  // Return: top left, top, top right, left, right, bot left, bot, bot right
  positions output;
  for (int dx = -1; dx < 2; dx++) {
    for (int dy = -1; dy < 2; dy++) {
      if (!(dx == 0 && dy == 0)) {
        output.push_back({dx, dy});
      }
    }
  }
  return output;
}

int update_seats(const input_type &input_, positions &seat_positions,
                 neighbor_map &neighbors, int adjacent_seats) {
  // Copy seat arrangements
  auto seats = input_;

  while (true) {
    // Need to keep track of the old configuration while updating the new
    auto old_seats = seats;

    // Keep track if we performed a change
    auto changed(false);

    // Go through each position and check for the rules
    for (auto &pos : seat_positions) {
      auto row = pos.first, col = pos.second;

      // Check how many neighbors are occupied
      auto occupied(0);
      for (auto &pos_n : neighbors[{row, col}]) {
        if (old_seats[pos_n.first][pos_n.second] == '#') {
          occupied++;
        }
      }

      // Update rules
      if (old_seats[row][col] == 'L' && occupied == 0) {
        seats[row][col] = '#';
        changed = true;
      } else if (old_seats[row][col] == '#' && occupied >= adjacent_seats) {
        seats[row][col] = 'L';
        changed = true;
      }
    }

    // We are done when no more seats are changing
    if (!changed) {
      break;
    }
  }
  // Count the number of # in the final configuration
  int occupied_seats(0);
  for (auto &seat : seats) {
    occupied_seats += std::count(seat.begin(), seat.end(), '#');
  }
  return occupied_seats;
}

neighbor_map get_neighbors_part1(const input_type &input,
                                 positions &seat_position) {
  auto adjacent = get_neighbor_directions();
  neighbor_map neighbors;

  // Go through each position and see if we have an empty seat next to us
  for (auto &seat : seat_position) {
    auto row = seat.first, col = seat.second;
    positions neighboring;
    for (auto &dxdy : adjacent) {
      auto dx = dxdy.first, dy = dxdy.second;
      if (input[row + dx][col + dy] == 'L') {
        neighboring.push_back({row + dx, col + dy});
      }
    }
    neighbors[seat] = neighboring;
  }
  return neighbors;
}

// Implement part one solution

output_type day11::solve_part1(const input_type &input_) {
  auto seat_positions = get_seat_positions(input_);
  auto neighbors = get_neighbors_part1(input_, seat_positions);

  return update_seats(input_, seat_positions, neighbors, 4);
}

neighbor_map get_neighbors_part2(const input_type &input,
                                 positions &seat_position) {
  auto adjacent = get_neighbor_directions();
  neighbor_map neighbors;

  // Go through each position and see if we can find an empty seat
  for (auto &seat : seat_position) {
    auto row = seat.first, col = seat.second;
    positions neighboring;

    // Traverse in direction dx,dy until we reach a seat or the end
    for (auto &dxdy : adjacent) {
      auto dx = dxdy.first, dy = dxdy.second;
      auto row_ = row + dx, col_ = col + dy;
      while (true) {
        if (input[row_][col_] != '.') {
          break;
        }
        row_ += dx;
        col_ += dy;
      }
      // Check if we reached a seat (remember we pad with " ")
      if (input[row_][col_] == 'L') {
        neighboring.push_back({row_, col_});
      }
    }
    neighbors[seat] = neighboring;
  }
  return neighbors;
}

// Implement part two solution
output_type day11::solve_part2(const input_type &input_) {
  auto seat_positions = get_seat_positions(input_);
  auto neighbors = get_neighbors_part2(input_, seat_positions);
  return update_seats(input_, seat_positions, neighbors, 5);
}
