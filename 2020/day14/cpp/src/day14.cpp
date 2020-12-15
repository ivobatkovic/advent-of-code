#include "day14.hpp"

#include <math.h>

#include <regex>
#include <unordered_map>

#include "utils.hpp"
using day14::input_type;
using day14::output_type;

std::vector<int64_t> get_bits(int64_t val);

input_type day14::transform_input(std::vector<std::string> &input) {
  input_type output;
  std::tuple<std::string, std::vector<int>> instructions;
  std::string mask;
  std::vector<int> address_val;
  std::regex rgx_mask("([\\[0|1|X]{36})");
  std::regex rgx_num("(\\d+)");

  for (auto &inp : input) {
    // Obtain the mask input
    if (std::regex_search(inp, std::regex("^(mask)"))) {
      output.push_back(std::make_tuple(mask, address_val));
      mask.clear();
      address_val.clear();

      std::smatch sm;
      std::regex_search(inp, sm, rgx_mask);
      mask = sm[0];
      // Obtain address and value
    } else {
      std::smatch sm;
      std::string i = inp;
      while (std::regex_search(i, sm, rgx_num)) {
        address_val.push_back(std::stoi(sm[0]));
        i = sm.suffix();
      }
    }
  }
  // Add final entry
  output.push_back(std::make_tuple(mask, address_val));

  // Remove the first empty entry
  output.erase(output.begin());

  return output;
}

input_type day14::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

// Implement part one solution
output_type day14::solve_part1(const input_type &input_) {
  // Memory map to place values at addresses
  std::unordered_map<int64_t, int64_t> memory;

  // Go through each input instruction
  for (auto &[mask, mem_val] : input_) {
    // Create the mask we are using
    std::string on_s, enable_s;
    for (auto &m : mask) {
      on_s += (m == '1') ? '1' : '0';
      enable_s += (m == 'X') ? '1' : '0';
    }
    auto on(std::stoll(on_s, 0, 2));
    auto enable(std::stoll(enable_s, 0, 2));

    // Go through write instructions
    for (size_t i = 0; i < mem_val.size(); i += 2) {
      auto address(mem_val[i]), val(mem_val[i + 1]);
      memory[address] = (enable & val) | on;
    }
  }

  // Go through the map and sum all written values
  int64_t sum(0);
  for (auto &m : memory) {
    sum += m.second;
  }
  return sum;
}

std::vector<int64_t> get_bits(int64_t val) {
  // If value is 0 return zero bit
  if (val == 0) {
    return std::vector<int64_t>({val});
  }
  // Otherwise get the most significant bit [10010] -> bit 5
  int most_sig_bit = int(log2(val));
  // Remove the most significant bit and get the next combinations
  auto bits = get_bits(val ^ (int64_t)(pow(2, most_sig_bit)));

  // Go through all other bits and append the combination
  // Example: val = [1001] gives combo [1001,1000,0001,0000]
  std::vector<int64_t> output_bits;
  for (auto &bit : bits) {
    output_bits.push_back(bit);
    output_bits.push_back(val ^ bit);
  }
  return output_bits;
}

// Implement part two solution
output_type day14::solve_part2(const input_type &input_) {
  // Memory dict to place values at addresses
  std::unordered_map<int64_t, int64_t> memory;

  // Go through each input instruction
  for (auto &[mask, mem_val] : input_) {
    // Create the mask we are using
    std::string on_s, enable_s, disable_s;
    for (auto &m : mask) {
      on_s += (m == '1') ? '1' : '0';
      enable_s += (m == 'X') ? '1' : '0';
      disable_s += (m != 'X') ? '1' : '0';
    }
    auto on(std::stoll(on_s, 0, 2));
    auto enable(std::stoll(enable_s, 0, 2));
    auto disable(std::stoll(disable_s, 0, 2));

    // Go through write instructions
    for (size_t i = 0; i < mem_val.size(); i += 2) {
      auto address(mem_val[i]), val(mem_val[i + 1]);

      // Compute all bit combinations of mask X
      auto bits = get_bits(enable);
      for (auto &bit : bits) {
        // (disable & address) gives all bits of val that are not
        // under the "X" mask. We combine it then with the active bits
        // from mask 1 and from the combinations from mask "X"
        memory[bit | (disable & address) | on] = val;
      }
    }
  }

  int64_t sum(0);
  for (auto &m : memory) {
    sum += m.second;
  }
  return sum;
}
