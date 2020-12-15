#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <string>
#include <vector>

/**
 * @brief SpaceImage class
 *
 */
class SpaceImage {
 public:
  std::vector<std::string> m_input;
  int m_width, m_height;

 public:
  /**
   * @brief Construct a new Space Image object
   *
   */
  SpaceImage();

  /**
   * @brief Construct a new Space Image object
   *
   * @param file_name input file
   * @param width of map
   * @param height of map
   */
  SpaceImage(std::string file_name, int width, int height);

  /**
   * @brief Solve puzzle one
   *
   * @return int
   */
  int corruption_check();

  /**
   * @brief Solve puzzle two
   *
   * @return std::string
   */
  std::string reconstruct_image();

  /**
   * @brief Print the map
   *
   * @param image_
   */
  void print_image(std::string image);
};

#endif

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif