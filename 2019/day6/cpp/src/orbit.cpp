#include "2019/day6/cpp/include/orbit.hpp"

#include <queue>

#include "utils/cpp/include/utils.hpp"

// Data struct just to simplify the FIFO queue
struct queue_data {
 public:
  std::string m_child;
  int m_parents;
  std::string m_start;

  queue_data(std::string name, int n_parents, std::string start = "")
      : m_child(name), m_parents(n_parents), m_start(start) {}
};

// Read input and initialize the parents and neighbor maps
Orbit::Orbit(std::string file_name) : m_parents(), m_neighbors() {
  auto input = utils::read_file(file_name);
  for (auto j = input.begin(); j < input.end(); j++) {
    size_t idx = (*j).find(")");
    std::string parent = (*j).substr(0, idx), child = (*j).substr(idx + 1, 3);
    m_parents[parent].push_back(child);
    m_neighbors[parent].push_back(child);
    m_neighbors[child].push_back(parent);
  }
}

int Orbit::get_number_of_orbits() {
  // Find the COM node and back track from here
  std::queue<queue_data> q;
  for (auto &child : m_parents["COM"]) {
    q.push(queue_data(child, 1));
  }

  // Keep going backwards in the orbital "tree"
  int n_orbits = 0;
  while (!q.empty()) {
    // Get a queue_data struct
    auto q_ = q.front();
    q.pop();

    // Add how many parents the node has
    n_orbits += q_.m_parents - 1;

    // Go through all the children this node has
    for (auto &child : m_parents[q_.m_child]) {
      q.push(queue_data(child, q_.m_parents + 1));
    }
  }

  // Return number of direct and indirect orbits
  return n_orbits + m_parents.size() - 1;
}

// Computes number of orbitals needed to go from star to end
int Orbit::get_orbitals(std::string start, std::string end) {
  // Find start node
  std::queue<queue_data> q;
  for (auto &neighbor : m_neighbors[start]) {
    q.push(queue_data(neighbor, 1, start));
  }

  while (!q.empty()) {
    // Get queue_data struct
    auto q_ = q.front();
    q.pop();

    // If node at the end - done
    if (q_.m_child == end) {
      return q_.m_parents - 2;
    }

    // Go through neighbors for the child
    auto n = m_neighbors[q_.m_child];
    for (auto &neighbor : n) {
      if (neighbor != q_.m_start) {
        q.push(queue_data(neighbor, q_.m_parents + 1, q_.m_child));
      }
    }
  }
  // Cannot find connection
  return -1;
}