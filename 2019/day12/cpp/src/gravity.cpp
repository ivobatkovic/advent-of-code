#include "gravity.hpp"

#include <math.h>

#include <regex>

#include "utils.hpp"

Gravity::Gravity(std::string file_name) : m_pos(), m_vel(), m_cycles() {
  auto input = utils::read_file(file_name);

  // Regex expression to extract numbers in format <x=X,y=Y,z=Z>
  std::regex rgx("-?\\d+");

  for (auto i : input) {
    std::smatch sm;
    std::vector<int> pos_xyz;
    while (regex_search(i, sm, rgx)) {
      pos_xyz.push_back(std::stoi(sm[0]));
      i = sm.suffix();
    }
    m_pos.push_back(pos_xyz);
  }

  m_vel = std::vector<std::vector<int>>(m_pos.size(),
                                        std::vector<int>(m_pos[0].size(), 0));
}

void Gravity::tick(int dim) {
  // Update dimension dim
  for (size_t i = 0; i < m_pos.size(); i++) {
    int ego = m_pos[i][dim];
    for (size_t j = 0; j < m_pos.size(); j++) {
      int other = m_pos[j][dim];

      m_vel[i][dim] += (ego < other) ? 1 : (ego > other) ? -1 : 0;
    }
  }
  for (size_t i = 0; i < m_pos.size(); i++) {
    m_pos[i][dim] += m_vel[i][dim];
  }
}

void Gravity::update(int time) {
  // Update all dimensions
  for (int i = 0; i < time; i++) {
    for (size_t k = 0; k < m_pos[0].size(); k++) {
      tick(k);
    }
  }
}

int Gravity::energy() {
  int energy(0);
  for (size_t i = 0; i < m_pos.size(); i++) {
    int kinetic(0), potential(0);
    for (size_t j = 0; j < m_pos[i].size(); j++) {
      potential += std::abs(m_pos[i][j]);
      kinetic += std::abs(m_vel[i][j]);
    }
    energy += potential * kinetic;
  }

  return energy;
}

int64_t Gravity::compute_cycles() {
  auto pos0 = m_pos;
  for (size_t dim = 0; dim < m_pos[0].size(); dim++) {
    int n_steps = 0;
    while (true) {
      tick(dim);
      n_steps++;
      bool cond(true);
      for (size_t i = 0; i < m_pos.size(); i++) {
        cond = (cond && m_pos[i][dim] == pos0[i][dim] && m_vel[i][dim] == 0);
      }

      if (cond) {
        m_cycles.push_back(n_steps);
        break;
      }
    }
  }

  int64_t total_cycles = 1;
  for (auto &cycle : m_cycles) {
    total_cycles = least_common_multiple(total_cycles, cycle);
  }

  return total_cycles;
}

int64_t Gravity::greatest_common_divisor(int64_t a_, int64_t b_) {
  while (b_ > 0) {
    auto a_tmp = a_, b_tmp = b_;
    a_ = b_tmp;
    b_ = a_tmp % b_tmp;
  }
  return a_;
}

int64_t Gravity::least_common_multiple(int64_t a_, int64_t b_) {
  return (a_ * b_ / greatest_common_divisor(a_, b_));
}
