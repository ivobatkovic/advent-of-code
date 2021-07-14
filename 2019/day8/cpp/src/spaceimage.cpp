#include "2019/day8/cpp/include/spaceimage.hpp"

#include <algorithm>
#include <iostream>

#include "utils/cpp/include/utils.hpp"

SpaceImage::SpaceImage() : m_input(), m_width(), m_height() {}

SpaceImage::SpaceImage(std::string file_name, int width, int height)
    : m_input(), m_width(width), m_height(height) {
  // Read the input "picture"
  m_input = utils::read_file(file_name);
}

int SpaceImage::corruption_check() {
  // Input string
  std::string image = m_input[0];

  // Each layer is of size (width*height), and <image> contains multiple layers
  // Go through each layer and count the number of zeros
  std::size_t start(0);
  std::vector<int> n_zeros;
  while (start < image.size()) {
    auto layer = image.substr(start, m_width * m_height);
    n_zeros.push_back(std::count(layer.begin(), layer.end(), '0'));
    start += m_width * m_height;
  }

  // Find layer with fewest zeros
  auto min_index =
      std::min_element(n_zeros.begin(), n_zeros.end()) - n_zeros.begin();
  std::string layer =
      image.substr(min_index * m_width * m_height, m_width * m_height);

  // Return number of 1s multiplied by 2s
  return std::count(layer.begin(), layer.end(), '1') *
         std::count(layer.begin(), layer.end(), '2');
}

std::string SpaceImage::reconstruct_image() {
  // Get input "image"
  std::string image = m_input[0];

  // Initialize output image
  std::string output(m_width * m_height, '2');
  std::size_t start(0);

  // Go through each layer
  while (start < image.size()) {
    std::string layer = image.substr(start, m_width * m_height);
    for (std::size_t o = 0; o < output.size(); o++) {
      // If the output layer is 2 then it is transparent, so we can update it.
      output[o] = (output[o] == '2') ? layer[o] : output[o];
    }
    start += m_width * m_height;
  }
  return output;
}

void SpaceImage::print_image(std::string image_) {
  // Print row by row
  for (int row = 0; row < m_height; row++) {
    for (int col = 0; col < m_width; col++) {
      std::cout << ((image_[row * m_width + col] == '1') ? '#' : ' ');
    }
    std::cout << "\n";
  }
}
