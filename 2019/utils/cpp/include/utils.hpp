#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace utils {

  /**
   * @brief Split a string with delimiter
   * 
   * @param str 
   * @param delim 
   * @return std::vector<std::string> 
   */
  template <typename T>
  void splitString(std::string str, char delim,std::vector<T> &split)
  {
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
      end = str.find(delim, start);
      // If the template is a string, we need to preserve the whitespaces
      if (std::is_same<T, std::string>::value) {
        T value;
        for (auto &x_ : str.substr(start, end - start)) {
          value += x_;
        }
        split.push_back(value);
      // Otherwise, convert to a value
      } else {
        std::istringstream iss(str.substr(start, end - start));
        T value;
        iss >> value;
        split.push_back(value);
      }
    }
  }

  /**
   * @brief Read lines of a file
   * 
   * @return true if successful
   * @return false otherwise
   */
  template<typename T>
  bool readFile(std::string fileName, std::vector<T> &x)
  {
    std::ifstream file(fileName);
    if (!file)
    {
      std::cerr << "Cannot open the File : " << fileName << std::endl;
      std::exit(-1);
    }
    std::string line;
    while (std::getline(file, line)) {
      if (line.size() > 0) {
        // If the template is a string, preserve whitespaces
        if (std::is_same<T,std::string>::value) {
          T value;
          for (auto& x_ : line) {
            value += x_;
          }
          x.push_back(value); 
        // Otherwise convert to a value
        } else {
          std::istringstream iss(line);
          T value;
          iss >> value;
          x.push_back(value);
        }      
      }
    }
    file.close();
    return true;
  }

  /**
   * @brief Read lines of a .csv file
   * 
   * @return true 
   * @return false 
   */
  template <typename T>
  bool readCSVFile(std::string fileName, std::vector<std::vector<T>> &output)
  {
    std::ifstream file(fileName);
    if (!file)
    {
      std::cerr << "Cannot open the File : " << fileName << std::endl;
      std::exit(-1);
    }
    std::string row, instruction;
    while (std::getline(file, row))
    {
      std::vector<T> split_string;
      utils::splitString(row, ',',split_string);
      output.push_back(split_string);
    }
    file.close();
    return true;
  }  
}

#endif