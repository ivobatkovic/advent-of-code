#include "day23.hpp"

#include "utils.hpp"

using day23::input_type;
using day23::output_type;

input_type day23::transform_input(std::vector<std::string> &input) {
  input_type output;

  for (auto &inp : input[0]) {
    output.push_back(int(inp) - 48);
  }
  return output;
}

input_type day23::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

std::unordered_map<int, int> day23::play_game(const input_type &input,
                                              int n_rounds, bool part_two) {
  // Initialize the game
  auto numbers = input;
  if (part_two) {
    int max_nr = *std::max_element(numbers.begin(), numbers.end());
    for (int i = max_nr + 1; i < 1000001; i++) {
      numbers.push_back(i);
    }
  }

  // Make a directional structure,e.g., 1->2->3->...->N->1
  std::unordered_map<int, int> cups;
  for (size_t i = 0; i < numbers.size() - 1; i++) {
    cups[numbers[i]] = numbers[i + 1];
  }
  cups[numbers.back()] = numbers.front();

  // Start with current nr in the beginning
  auto current_cup = numbers.front();

  // Go through each round
  for (int round = 0; round < n_rounds; round++) {
    // Get first, second, and third cup from the current_cup one
    auto first_cup = cups[current_cup];
    auto second_cup = cups[first_cup];
    auto third_cup = cups[second_cup];

    // Point the current cup to what the third one points to
    cups[current_cup] = cups[third_cup];

    // Get the next cup to append elements after
    auto next = current_cup - 1;
    while (true) {
      // Wrap around
      if (next == 0) {
        next = numbers.size();
      }
      // If the next cup has been removed, keep going
      if (next == first_cup || next == second_cup || next == third_cup) {
        next -= 1;
        // Otherwise, we have found the next destination cup
      } else {
        break;
      }
    }
    // Get the cup that the destination cup is pointing to
    auto number_after_next = cups[next];

    // Point the destination cup to the first_cup
    cups[next] = first_cup;

    // Point the third cup to what the destination cup pointed to
    cups[third_cup] = number_after_next;

    // Update the current cup to the one it is pointing to
    current_cup = cups[current_cup];
  }

  return cups;
}

// Implement part one solution
output_type day23::solve_part1(const input_type &input_, int n_rounds) {
  auto cups = play_game(input_, n_rounds);
  // Find the cup that "1" is pointing to, and keep going through the cups
  auto cup = cups[1];
  std::string output;
  for (size_t i = 0; i < cups.size() - 1; i++) {
    output += std::to_string(cup);
    cup = cups[cup];
  }
  return std::stoi(output);
}

// Implement part two solution
output_type day23::solve_part2(const input_type &input_, int n_rounds) {
  auto cups = play_game(input_, n_rounds, true);
  return size_t(cups[1]) * int64_t(cups[cups[1]]);
}
