#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
auto read_input(std::string fileName, T TransformFunc) -> std::vector<decltype(TransformFunc(std::string()))>
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        std::exit(-1);
    }
    std::string line;
    std::vector<decltype(TransformFunc(std::string()))> transformedLines;
    while (std::getline(file, line))
    {
        auto tmp = TransformFunc(line);
        transformedLines.push_back(tmp);
    }

    if (file.is_open())
    {
        file.close();
    }

    return transformedLines;
}

#endif // AOC_UTILS_H
