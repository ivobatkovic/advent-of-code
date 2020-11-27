#include "pong.hpp"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <tuple>
#include <iostream>
#include "ncurses.h"

// Initialize the intcode
Pong::Pong(std::string file_name, bool play) : m_intcode(),m_map(), 
    m_ball({0,0,0,0}), m_pad({0,0}), m_map_rendered(false),
    m_ball_rendered(false), m_score(0) {

  m_intcode = Intcode(file_name,{},false,false);

  if (play) {
    m_intcode.m_program[0] = 2;
  }

}

// Generate the map
int Pong::render_map() {

  while (true) {
    
    auto output = m_intcode();
    int x = std::get<1>(output);

    // If terminated
    if (std::get<0>(output)) {
      int nTwos = 0;
      for (auto &m : m_map) {
        if (m.second==2) { nTwos++; }
      }
      return nTwos;
    }

    // Update map
    auto output_y = m_intcode();
    int y = std::get<1>(output_y);

    auto output_t = m_intcode();
    int t = std::get<1>(output_t);

    m_map[std::pair<int,int>(y,x)] = t;
    }
}

// Select an input
int Pong::bot() {
  if (m_ball[3] == 1 && m_pad[1] < m_ball[1]) {
    return 1;
  }
  if (m_ball[3] == -1 && m_pad[1] > m_ball[1]) {
    return -1;
  }
  return 0;
}

// Run the game
int Pong::play() {

  signal(SIGINT, catch_ctrlc);
  initscr();
  
  while(true) {
    auto output = m_intcode();
    auto x = std::get<1>(output);

    // If terminated
    if (std::get<0>(output)) {
      endwin();
      return m_score;  
    }
    
    auto output_y = m_intcode();
    auto output_t = m_intcode();
    int y = std::get<1>(output_y);
    int t = std::get<1>(output_t);

    // Update rules
    if (!(x==-1 && y==0)) {
      m_map[std::pair<int,int>(y,x)] = t;

      if (t == 4) {
        m_ball_rendered = true;
        m_ball = std::vector<int64_t>{y,x,y-m_ball[0],x-m_ball[1]};
      }
      if (t == 3) {
        m_pad = std::vector<int64_t>{y,x};
      }
    } else {
      m_map_rendered = true;
      m_score = t;
      mvprintw(0, 0, "Score: %d\n",m_score);
      refresh();
    }

    if (m_map_rendered && m_ball_rendered) {
      render();
      m_intcode.m_input.push_back(bot());
      m_ball_rendered = false;
    }
  }
}

// Print the map
void Pong::render() {

  int height, width;
  getmaxyx(stdscr, height, width);

  int max_x(WINT_MIN);
  int max_y(WINT_MIN);

  for (auto &m : m_map)
  {
    max_x = (max_x < m.first.first) ? m.first.first : max_x;
    max_y = (max_y < m.first.second) ? m.first.second : max_y;
  }
  for (int row = 0; row < max_x + 1; row++)
  {
    std::string str = "";
    for (int col = 0; col < max_y + 1; col++) {
      int mp = m_map[std::pair<int, int>(row, col)];
      if (mp == 4) {
        str += "o";
      } else if ( mp == 3) {
        str += "=";
      } else if (mp == 2) {
        str += "x";
      } else if (mp == 1) {
        str += "|";
      } else {
        str += " ";
      }
      if (col > width - 3) {
        break;
      }
      mvprintw(row+1,0,str.c_str());
    }
    if (row+1 > height -3) {
      break;
    }
  }
  refresh();
}

// Catch a ctrl-c event
void Pong::catch_ctrlc(int s) {
  endwin();
  printf("Caught signal %d\n",s);
  exit(1);
}
