#include "maze.hpp"
#include "utils.hpp"
#include <queue>

// Data structure for the queue
struct queue_data
{
  int m_depth;
  std::vector<std::pair<int, int>> m_pos;
  std::set<char> m_keys;

  queue_data(int n1, std::vector<std::pair<int, int>> n2, std::set<char> n3) : 
      m_depth(n1), m_pos(n2), m_keys(n3) {}

  bool operator<(const struct queue_data &other) const {
    return m_depth > other.m_depth;
  }
};

Maze::Maze(std::string file_name, bool multiple_robots) : 
    m_grid(), m_y(), m_x(), m_total_keys(), m_pos() {

  utils::readFile(file_name,m_grid);
  find_start_and_keys();
  m_pos = initialize_position(multiple_robots);

}

// Go through the maze and find the starting position + all keys
void Maze::find_start_and_keys() {

  auto width = m_grid[0].size();

  std::string linear_grid = "";
  for (auto &str : m_grid) {
    linear_grid += str;
  }

  // Start position
  auto start_index = linear_grid.find('@');
  m_y = start_index / width;
  m_x = start_index % width;

  // Store all lower case keys
  for (auto &chr : linear_grid) {
    if (islower(chr)) {
      m_total_keys.insert(chr);
    }
  }

}

std::vector<std::pair<int, int>> Maze::initialize_position(bool multi_robots) {

  // Reshape the map if there are multiple robots
  auto len = m_grid[0].size();
  if (multi_robots) {
    m_grid[m_y-1] = m_grid[m_y-1].substr(0,m_x) + "#" + 
                    m_grid[m_y-1].substr(m_x+1, len-(m_x+1));
    m_grid[m_y]   = m_grid[m_y].substr(0, m_x-1) + "###" + 
                    m_grid[m_y].substr(m_x + 2, len - (m_x + 2));
    m_grid[m_y+1] = m_grid[m_y+1].substr(0, m_x) + "#" + 
                    m_grid[m_y+1].substr(m_x + 1, len - (m_x + 1));

    std::pair<int,int> p1(m_y-1, m_x-1), p2(m_y+1, m_x+1);
    std::pair<int,int> p3(m_y+1, m_x-1), p4(m_y-1, m_x+1);

    return std::vector<std::pair<int,int>>({p1,p2,p3,p4});

  // Otherwise return positions
  } else {
    return std::vector<std::pair<int,int>>({std::make_pair(m_y,m_x)});
  }
}

std::vector<std::tuple<int, int, int, char>> 
    Maze::reachable_keys(int y, int x, std::set<char> keys) {

  // Depth, y, x, key
  std::vector<std::tuple<int,int,int,char>> dist_to_key;
  std::queue<std::tuple<int,int,int>> q;
  q.push(std::make_tuple(y,x,0));
  
  // Keeping track of visited nodes
  std::set<std::pair<int,int>> visited;

  // Search directions
  std::vector<std::vector<int>> directions({ {1,0},{-1,0},{0,1},{0,-1}});

  // Keep doing until we can't go no more 
  while (!q.empty()) {
    auto q_ = q.front(); q.pop();
    auto y_ = std::get<0>(q_);
    auto x_ = std::get<1>(q_);
    auto depth = std::get<2>(q_);

    // If the grid elemnt is a key and we dont have it
    if (islower(m_grid[y_][x_]) and !keys.count(m_grid[y_][x_])) {
      dist_to_key.push_back(std::make_tuple(depth, y_, x_, m_grid[y_][x_]));
      continue; // Maybe not here
    }

    for (auto &dir : directions) {
      auto y_new = dir[0] + y_;
      auto x_new = dir[1] + x_;

      // Skip if we've been here
      if (visited.count(std::make_pair(y_new,x_new))) {
        continue;
      }
      visited.insert(std::make_pair(y_new,x_new));

      // Keep going in new direction
      auto value = m_grid[y_new][x_new];
      if (value != '#' && (!isupper(value) || keys.count(tolower(value)))) {
        q.push(std::make_tuple(y_new,x_new,depth+1));
      }
    }
  }
  return dist_to_key;
}

int Maze::compute_shortest_path() {

  // Go out and collect keys
  std::priority_queue<queue_data> q_;
  q_.push(queue_data(0,m_pos,std::set<char>()));

  // Visited nodes
  std::set< std::pair<std::vector<std::pair<int,int>>,std::set<char>>> visited;

  while (!q_.empty()) {

    // Get node with smallest depth
    queue_data q = q_.top(); q_.pop();

    // If we have all keys we are done
    auto keys = q.m_keys;
    if (keys == m_total_keys) {
      return q.m_depth;
    }

    // Skip if we've been here
    if (visited.count(std::make_pair(q.m_pos,q.m_keys))) {
      continue;
    }
    visited.insert(std::make_pair(q.m_pos,q.m_keys));

    // Loop through the positions (if multiple robots)
    for (size_t i = 0; i < q.m_pos.size(); i++) {
      // Get all reachable keys
      auto rk = reachable_keys(q.m_pos[i].first, q.m_pos[i].second, q.m_keys);

      // Go through all keys we can reach
      for (size_t j = 0; j < rk.size(); j++) {
        int d = std::get<0>(rk[j]);
        int y = std::get<1>(rk[j]), x = std::get<2>(rk[j]);
        char keyy = std::get<3>(rk[j]);
        
        // Update the new position
        auto new_pos = q.m_pos;
        new_pos[i] = std::make_pair(y,x);
        auto setkey = q.m_keys; setkey.insert(keyy);
        q_.push(queue_data(q.m_depth+d,new_pos,setkey));
      }
    } 
  }
  return -1;
}