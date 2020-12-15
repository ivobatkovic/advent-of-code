#ifndef _DONUT_H_
#define _DONUT_H_

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<std::vector<int>>> portal_map;
typedef std::map<std::vector<int>,
                 std::tuple<std::vector<int>, int, std::string>>
    reach_map;

/**
 * @brief Donut class
 *
 */
class Donut {
 public:
  std::vector<std::string> m_grid;
  portal_map m_portals;
  reach_map m_reach;

  /**
   * @brief Construct a new Donut object
   *
   * @param file_name
   */
  Donut(std::string file_name);

  /**
   * @brief Find the portals and connect them to each other
   *
   * @param portals
   * @param reach
   */
  void find_portals(portal_map &portals, reach_map &reach);

  /**
   * @brief Solve part one and two
   *
   * @param level_check
   * @return int
   */
  int shortest_path(bool level_check = false);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif