#ifndef _JIGGSAW_H_
#define _JIGGSAW_H_

#include <map>
#include <string>
#include <unordered_map>
#include <vector>
class Jiggsaw {
 public:
  using image_type = std::vector<std::string>;
  using images_type = std::unordered_map<std::string, image_type>;
  using image_sides_type = images_type;

  images_type m_images;
  image_sides_type m_image_sides;
  std::map<std::pair<int, int>, std::pair<std::string, image_type>>
      m_complete_images;
  image_type m_combined_image;
  int m_xmin, m_ymin, m_xmax, m_ymax;

  Jiggsaw(const images_type &images);
  image_sides_type compute_image_sides();
  std::string get_side(std::string tile, int dir = 0);
  void rotate(std::vector<std::string> &tile, int n_times);
  void reverse(std::vector<std::string> &tile);
  void flip(std::vector<std::string> &tile);
  void organize_tile(std::string tile, int dir_to, int dir_from);
  bool find_matching_tile(std::string current, std::string tile, int dir_to);
  void solve();
  void combine_images();
  std::vector<std::pair<int, int>> get_corners();

  int find_monsters(image_type &monster);
  int get_rough_waters(image_type &monster);
};

#endif