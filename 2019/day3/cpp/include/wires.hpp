#ifndef _WIRES_H_
#define _WIRES_H_

#include <string>
#include <vector>

/**
 * @brief Class that computes intersections of two wires
 *
 */
class Wires {
 public:
  std::vector<std::vector<std::string>> m_wire;
  int m_distance;
  int m_steps;

  /**
   * @brief Construct a new Wires object
   *
   */
  Wires();

  /**
   * @brief Construct a new Wires object and compute all intersection
   * points and their corresponding distances and lenghts
   *
   * @param file_name_ input file
   */
  Wires(std::string file_name);

  /**
   * @brief Solve the puzzle
   *
   */
  void solve();

  /**
   * @brief Given the input of the wire sequences, compute a wire segment
   * consisting of a 2D-vector with shape <{x,y,orientation,length_along_wire}>
   *
   * @param wire_segments
   */
  void compute_wire_segments(std::vector<std::vector<int>> wire_segments[2]);

  /**
   * @brief Goes through the wiresegments for two wires and checks
   * if the segments overlap
   *
   * @param wire1
   * @param wire2
   */
  void intersect_wires(std::vector<std::vector<int>> &wire1,
                       std::vector<std::vector<int>> &wire2);

  /**
   * @brief Compute line intersection of lines [A B] and [C D]
   *
   * @param A [x1 y1]
   * @param B [x2 y2]
   * @param C [x3 y3]
   * @param D [x4 y4]
   * @param point  point of the intersection
   * @param steps  summed distance along each wire to the intersection
   * @return true  intersection exists
   * @return false intersection does not exist
   */
  bool intersect(std::vector<int> &A, std::vector<int> &B, std::vector<int> &C,
                 std::vector<int> &D, std::vector<int> &point, int &steps);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif