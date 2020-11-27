#include "asci.hpp"
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "ncurses.h"
#include <signal.h>
#include <iostream>

Asci::Asci(std::string file_name) : 
    m_file_name(file_name), m_intcode(), m_mp() {

  m_intcode = Intcode(m_file_name,{},false,false);
  m_mp = get_map();

}

std::map<std::pair<int,int>,int> Asci::get_map() {

  // Initial position
  int y(0), x(0);

  std::map<std::pair<int,int>,int> map;

  // Go through the intcode output
  while (true) {
    auto output = m_intcode();
    if (std::get<0>(output)) { 
      break;
    }
    if (std::get<1>(output) == 10) {
      y += 1;
      x = 0;
    } else {
      map[std::make_pair(y, x)] = std::get<1>(output);
      x += 1;
    }
  }
  return map;
}

int Asci::compute_intersections(bool print_map_) {

  int tot(0);
  for (auto &m : m_mp) {
    // If the value is 35 ('#') check top, left, right, bottom
    if (m.second == 35) {
      int y = m.first.first, x = m.first.second;
      if (m_mp[std::make_pair(y, x + 1)] == 35 &&
          m_mp[std::make_pair(y, x - 1)] == 35 &&
          m_mp[std::make_pair(y - 1, x)] == 35 &&
          m_mp[std::make_pair(y + 1, x)] == 35) {
        m_mp[std::make_pair(y,x)] = int('O');
        tot += y*x;
      }
    }
  }
  // Print the map
  if (print_map_) {
    print_map();
  }
  return tot;
}

void Asci::print_map() {

  int max_x(WINT_MIN);
  int max_y(WINT_MIN);

  for (auto &m : m_mp) {
    max_y = (max_y < m.first.first) ? m.first.first : max_y;
    max_x = (max_x < m.first.second) ? m.first.second : max_x;
  }

  for (int row = 0; row < max_y+1;row++) {
    for (int col = 0; col < max_x+1; col++) {
      std::cout << char(m_mp[std::make_pair(row,col)]);
    }
    std::cout<<std::endl;
  }
}

void Asci::find_start_pose(int &x, int &y, double &theta) {
  // Look foor (<,v,^,>)
  for (auto &m : m_mp) {
    if (m.second == 94 || m.second == 60 || m.second == 62 || m.second == 118) {
      y = m.first.first;
      x = m.first.second;
      break;
    }
  }
  // Initial point - figure out orientation
  auto v = m_mp[std::make_pair(y,x)];
  if (v == int('^')) {
    theta = M_PI_2;
  } else if (v == int('<')) {
    theta = -M_PI;
  } else if (v == int('>')) {
    theta = 0;
  } else {
    theta = -M_PI_2;
  }
}

std::string Asci::traverse_scaffold() {
  // Starting position
  int x,y;
  double theta,theta_;
  find_start_pose(x,y,theta);
  double dy=(-sin(theta)), dx=(cos(theta));

  // Keep track of how many straight steps
  int straight(0); 
  std::string instruction_string = "";

  // Keep going until we reach the end
  while (true) {

    std::pair<int,int> pos(y+dy,x+dx);
    // If scaffold infront of us, keep going
    if (m_mp[pos] == int('#') || m_mp[pos] == int('O')) {
      m_mp[std::make_pair(y,x)] = int('O');
      straight++;
      y = y+dy;
      x = x+dx;  
    }
    // Otherwise, see where the scaffold turns
    else {
      if      (m_mp[std::make_pair(y-1,x)] == int('#')) { theta_ = M_PI_2;}
      else if (m_mp[std::make_pair(y+1,x)] == int('#')) { theta_ = -M_PI_2;}
      else if (m_mp[std::make_pair(y,x-1)] == int('#')) { theta_ = -M_PI;}
      else if (m_mp[std::make_pair(y,x+1)] == int('#')) { theta_ = 0;}
      // Reached the end
      else {
        m_mp[std::make_pair(y,x)] = int('x');
        if (straight > 0) {
          instruction_string += std::to_string(straight);
        }
        return instruction_string;
      }

      // Apply the steps taken and reset <straight>
      if (straight > 0) {
        instruction_string += std::to_string(straight)+",";
        straight = 0;
      }

      // Find angle between theta and theta_
      double d = sin(theta+M_PI_2)*sin(theta_) + cos(theta+M_PI_2)*cos(theta_);
      d = (d>1) ? 1 : ((d<-1) ? -1 : d);

      if (abs(acos(d)) < 1e-4) {
        instruction_string += "L,";
        theta = theta+M_PI_2;
      } else {
        instruction_string += "R,";
        theta = theta - M_PI_2;
      }

      // Update directions      
      dy = int(round(-sin(theta)));
      dx = int(round(cos(theta)));
    }
  }
  return "Solution failed";
}

void Asci::find_movement_routine(
    std::string &routine, std::string &A,std::string &B,std::string &C) {

  // Get the instruction string
  std::string str0 = traverse_scaffold()+",";

  // Chop up the string from 20 characters to 1 characters for A
  for (size_t an = std::min(size_t(20),str0.size()); an > 0; an--) {
    // Don't include the comma
    if (str0.substr(0,an).back() == ',') {
      continue;
    }
    // Otherwise, remove all such occurences, and do same thing for B
    else {
      std::string str1 = str0;
      boost::erase_all(str1, str0.substr(0,an+1));

      // Chop up the string from 20 characters to 1 characters for B
      for (size_t bn = std::min(size_t(20),str1.size()); bn > 0; bn--) {
        // Don't include the comma
        if (str1.substr(0,bn).back() == ',') {
          continue;
        // Otherwise, remove all such occurences, and do same thing for C
        } else {
          auto str2 = str1;
          boost::erase_all(str2, str1.substr(0, bn + 1));
          // Chop up the string from 20 characters to 1 characters for C
          for (size_t cn = std::min(size_t(20), str2.size()); cn > 0; cn--) {
            // Don't include the comma
            if (str2.substr(0,cn).back() == ',') {
              continue;
              // Otherwise, remove all such occurences
            } else {
              auto str3 = str2;
              boost::erase_all(str3, str2.substr(0, cn + 1));

              // If remainder is empty, we are done
              if (str3.size() == 0 ) {
                // Build the routine
                A = str0.substr(0, an);
                B = str1.substr(0,bn);
                C = str2.substr(0,cn);
                boost::replace_all(str0, A, "A");
                boost::replace_all(str0, B, "B");
                boost::replace_all(str0, C, "C");
                str0.pop_back();
                routine = str0;
                return;
              }
            }
          }
        }
      }
    }
  }
}

std::vector<int64_t> Asci::construct_input(bool print_iterations) {
  std::string routine, A, B, C;
  find_movement_routine(routine,A,B,C);
  std::vector<int64_t> inp;
  for (auto &r : routine) { inp.push_back(int(r)); }
  inp.push_back(10);
  
  for (auto &r : A) { inp.push_back(int(r)); }
  inp.push_back(10);
  
  for (auto &r : B) { inp.push_back(int(r)); }
  inp.push_back(10);
  
  for (auto &r : C) { inp.push_back(int(r)); }
  inp.push_back(10);

  if(print_iterations) { inp.push_back(int('y')); } 
  else { inp.push_back(int('n')); }
  inp.push_back(10);

  return inp;
}


int Asci::collect_dust(bool print_iterations) {

  // Pass the intput to the intcode computer
  auto input = construct_input(print_iterations);
  m_intcode = Intcode(m_file_name,input,false,false);
  m_intcode.m_program[0] = 2;

  // Run until it terminates
  if(!print_iterations) {
    while(true) {
      auto output = m_intcode();
      if (std::get<0>(output)) {
        return std::get<1>(output);
      }
    }
  } else {
    return print_video_feed();
  }
}


int Asci::print_video_feed() {

  signal(SIGINT, catch_ctrlc);
  initscr();

  int height, width;
  getmaxyx(stdscr, height, width);

  std::string valid = "#.<^v>\n";
  int max_x(WINT_MIN);
  int max_y(WINT_MIN);

  for (auto &m : m_mp) {
    max_y = (max_y < m.first.first) ? m.first.first : max_y;
    max_x = (max_x < m.first.second) ? m.first.second : max_x;
  }

  std::map<std::pair<int,int>,int> map;
  while (true) {
    int y(0),x(0);
    bool skip(false);
    // Run until termination
    while (true) {
      auto output = m_intcode();
      int o = std::get<1>(output);
      if (std::get<0>(output)) {
        endwin();
        return o;}

      if (valid.find(char(o % 256)) == std::string::npos ||
          (x == 0 && o == 10)) {
        skip = true;
      }
      // char(10) == '\n' new line
      if (o == 10) {
        if(!skip) { y+=1; }
        x = 0; skip = false;
        if (y > max_y-1) { break; }
      // else, fill the map
      } else if (!skip) {
        map[std::make_pair(y,x)] = o;
        x += 1;
      }
    }
    // Print the map
    for (int row = 0; row < max_y+1; row++) {
      std::string msg = "";
      for (int col = 0; col < max_x+1; col++) {
        if (col > width -3) {break;}
        msg += char(map[std::make_pair(row,col)]);
      }
      if (row > height -3) { break;}
      mvprintw(row, 0, msg.c_str());
    }
    refresh();
  }
  return -1;
}

void Asci::catch_ctrlc(int s)
{
  endwin();
  printf("Caught signal %d\n", s);
  exit(1);
}