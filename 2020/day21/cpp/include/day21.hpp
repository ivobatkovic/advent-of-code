#ifndef _DAY21_H_
#define _DAY21_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <map>
#include <set>
#include <string>
#include <vector>

namespace day21 {

// Default input type for each day: need to change
using output_type1 = int;
using output_type2 = std::string;

using set_type = std::set<std::string>;
using map_type = std::map<std::string, set_type>;
using match_type = std::pair<set_type, map_type>;
using input_type =
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>;

// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

match_type match_allergens(const input_type &input);

output_type1 solve_part1(const input_type &input);

output_type2 solve_part2(const input_type &input);
}  // namespace day21

#endif
