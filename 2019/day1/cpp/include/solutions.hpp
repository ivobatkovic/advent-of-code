#ifndef _2019_DAY1_H_
#define _2019_DAY1_H_

#include <string>
#include <vector>

namespace day1 {

using output_type = std::string;

std::string read_input(std::string file_name = "2019/day1/data/input.txt");

output_type solve_part1(const std::string &input_string);

output_type solve_part2(const std::string &input_string);

}  // namespace day1

#endif
