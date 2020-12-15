#include "droid.hpp"

#include <signal.h>

#include <queue>

#include "ncurses.h"

Droid::Droid(std::string file_name) : m_intcode(), m_map() {
  m_intcode = Intcode(file_name, {}, false, false);
}

// Return new output pair depdning on input
std::pair<int, int> Droid::one_step(int y, int x, int input) {
  y -= (input == 1) ? 1 : ((input == 2) ? -1 : 0);
  x += (input == 3) ? 1 : ((input == 4) ? -1 : 0);
  return std::make_pair(y, x);
}

std::tuple<int, int, int> Droid::repair_oxygen(int y_, int x_) {
  // Initialize starting position
  std::map<std::pair<int, int>, int> parents;
  parents[std::make_pair(y_, x_)] = 1;
  m_map[std::make_pair(y_, x_)] = 1;

  // Use BFS to explore the "map"
  std::queue<std::tuple<int, int, Intcode, int>> q;
  q.push(std::make_tuple(y_, x_, m_intcode, 0));

  // Output solution
  std::tuple<int, int, int> solution;

  // Using ncurses
  signal(SIGINT, catch_ctrlc);
  initscr();

  // Run until we have explored everything
  while (!q.empty()) {
    // Get a queue_data struct
    auto q_ = q.front();
    q.pop();
    auto y = std::get<0>(q_);
    auto x = std::get<1>(q_);
    auto ic = std::get<2>(q_);
    auto depth = std::get<3>(q_);

    for (int i = 0; i < 5; i++) {
      auto xy_new = one_step(y, x, i);
      auto y_new = xy_new.first;
      auto x_new = xy_new.second;

      // If we havent visited the state
      if (parents.count(xy_new) != 1) {
        parents[xy_new] = 1;

        Intcode ic_ = ic;
        auto out = std::get<1>(ic_(i));

        if (out == 1) {
          m_map[xy_new] = 1;
          q.push(std::make_tuple(y_new, x_new, ic_, depth + 1));
        } else if (out == 2) {
          m_map[xy_new] = 2;
          solution = std::make_tuple(y_new, x_new, depth + 1);
        } else {
          m_map[xy_new] = 0;
        }
      }
    }
    render();
  }
  endwin();
  return solution;
}

int Droid::fill_oxygen(int y_, int x_) {
  // Initialize starting position
  std::map<std::pair<int, int>, int> parents;
  parents[std::make_pair(y_, x_)] = 1;

  // BFS search in the map
  std::queue<std::tuple<int, int, int>> q;
  q.push(std::make_tuple(y_, x_, 0));

  signal(SIGINT, catch_ctrlc);
  initscr();

  // Keep going through all empty map spaces and keep count
  auto max_depth = -1;
  while (!q.empty()) {
    auto q_ = q.front();
    q.pop();
    auto y = std::get<0>(q_);
    auto x = std::get<1>(q_);
    auto depth = std::get<2>(q_);

    for (int i = 0; i < 5; i++) {
      auto xy_new = one_step(y, x, i);
      auto y_new = xy_new.first;
      auto x_new = xy_new.second;

      if (parents[xy_new] != 1) {
        parents[xy_new] = 1;

        if (m_map[xy_new] == 1) {
          m_map[xy_new] = 2;
          max_depth = depth + 1;
          q.push(std::make_tuple(y_new, x_new, depth + 1));
        }
      }
    }
    render();
  }
  endwin();
  return max_depth;
}

// Print the map
void Droid::render() {
  int height, width;
  getmaxyx(stdscr, height, width);

  int max_x(WINT_MIN), min_x(WINT_MAX);
  int max_y(WINT_MIN), min_y(WINT_MAX);

  for (auto& m : m_map) {
    max_x = (max_x < m.first.first) ? m.first.first : max_x;
    max_y = (max_y < m.first.second) ? m.first.second : max_y;

    min_x = (min_x > m.first.first) ? m.first.first : min_x;
    min_y = (min_y > m.first.second) ? m.first.second : min_y;
  }

  for (int row = min_x; row < max_x + 1; row++) {
    std::string str = "";
    for (int col = min_y; col < max_y + 1; col++) {
      int mp = m_map[std::pair<int, int>(row, col)];
      str += (mp == 0) ? "X" : ((mp == 2) ? "O" : " ");
      if (col > width - 3) {
        break;
      }
      mvprintw(row - min_x, 0, str.c_str());
    }
    if (row - min_x > height - 3) {
      break;
    }
  }
  refresh();
}

void Droid::catch_ctrlc(int s) {
  endwin(); /* End curses mode		  */
  printf("Caught signal %d\n", s);
  exit(1);
}