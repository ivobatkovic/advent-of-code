#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

namespace utils {
  /**
   * @brief Read lines of a file
   * 
   * @return true if successful
   * @return false otherwise
   */
  template<typename T>
  bool readFile(std::string, std::vector<T> &);

  /**
   * @brief Read lines of a .csv file
   * 
   * @return true 
   * @return false 
   */
  template <typename T>
  bool readCSVFile(std::string, std::vector<std::vector<T>> &);
  
  /**
   * @brief Split a string with delimiter
   * 
   * @param str 
   * @param delim 
   * @return std::vector<std::string> 
   */
  template <typename T>
  void splitString(std::string, char,std::vector<T> &);
  
}

#endif