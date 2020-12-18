#ifndef _DAY16_H_
#define _DAY16_H_

#ifndef SOURCE_DIR
#define SOURCE_DIR ".."
#endif

#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace day16 {

// Default input type for each day: need to change
using output_type = int64_t;
using valid_type =
    std::unordered_map<std::string, std::vector<std::vector<int>>>;
using ticket_type = std::vector<std::vector<int>>;
using input_type = std::pair<valid_type, ticket_type>;

ticket_type find_all(std::vector<std::string> strng, std::regex rgx);
// Transformation method: parse input -> input_type
input_type transform_input(std::vector<std::string> &input);

// Read the input
input_type read_input(std::string file_name = std::string(SOURCE_DIR) +
                                              "/data/input.txt");

int check(int digit, const valid_type &valid);
output_type solve_part1(const input_type &input);

ticket_type get_valid_tickets(const input_type &input_);
std::unordered_set<int> get_valid_indices(std::string name, valid_type &valid,
                                          ticket_type &tickets,
                                          std::unordered_set<int> &indices);
std::unordered_map<std::string, int> match_field_to_index(ticket_type &tickets,
                                                          valid_type bounds);
output_type solve_part2(const input_type &input);
}  // namespace day16

#endif
