#include "2020/day22/cpp/include/day22.hpp"

#include <set>

#include "utils/cpp/include/utils.hpp"
using day22::input_type;
using day22::output_type;

input_type day22::transform_input(std::vector<std::string> &input) {
  input_type decks;
  std::vector<int> player;
  int player_nr = -1;

  for (auto &inp : input) {
    // Skip empty line
    if (inp.length() == 0) {
      continue;
    }

    if (inp.find("Player") != std::string::npos) {
      player_nr += 1;
      decks.push_back(player);
      player.clear();
    } else {
      player.push_back(std::stoi(inp));
    }
  }
  decks.push_back(player);
  decks.erase(decks.begin());

  return decks;
}

input_type day22::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

std::pair<std::vector<int>, int> day22::combat(std::vector<int> p1,
                                               std::vector<int> p2,
                                               bool recursive) {
  std::set<std::pair<std::vector<int>, std::vector<int>>> game_config;
  int winner = 0;

  while (true) {
    if (recursive) {
      if (game_config.count(std::make_pair(p1, p2))) {
        return std::make_pair(p1, 0);
      }
      game_config.insert(std::make_pair(p1, p2));
    }

    // Draw card
    auto c1 = p1[0], c2 = p2[0];

    winner = -1;
    if (((c1 <= int(p1.size()) - 1) && (c2 <= int(p2.size()) - 1)) &&
        recursive) {
      auto output = combat({p1.begin() + 1, p1.begin() + 1 + c1},
                           {p2.begin() + 1, p2.begin() + 1 + c2}, recursive);
      winner = output.second;
    }
    if (((c1 > c2) && (winner == -1)) || winner == 0) {
      std::vector<int> tmp1 = {p1.begin() + 1, p1.end()};
      tmp1.push_back(*p1.begin());
      tmp1.push_back(*p2.begin());
      std::vector<int> tmp2 = {p2.begin() + 1, p2.end()};
      p1 = tmp1;
      p2 = tmp2;
      winner = 0;
    } else {
      std::vector<int> tmp1 = {p1.begin() + 1, p1.end()};
      std::vector<int> tmp2 = {p2.begin() + 1, p2.end()};
      tmp2.push_back(*p2.begin());
      tmp2.push_back(*p1.begin());
      p1 = tmp1;
      p2 = tmp2;
      winner = 1;
    }

    if (p1.size() == 0) {
      return std::make_pair(p2, 1);
    } else if (p2.size() == 0) {
      return std::make_pair(p1, 0);
    }
  }
}

// Implement part one solution
output_type day22::solve_part1(const input_type &input_) {
  std::vector<int> p1 = input_[0];
  std::vector<int> p2 = input_[1];
  auto output = combat(p1, p2);

  int s = 0;
  for (int i = 0; i < int(output.first.size()); i++) {
    s += output.first[i] * (output.first.size() - i);
  }
  return s;
}

// Implement part two solution
output_type day22::solve_part2(const input_type &input_) {
  std::vector<int> p1 = input_[0];
  std::vector<int> p2 = input_[1];
  auto output = combat(p1, p2, true);

  int s = 0;
  for (int i = 0; i < int(output.first.size()); i++) {
    s += output.first[i] * (output.first.size() - i);
  }
  return s;
}
