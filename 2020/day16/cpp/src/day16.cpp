#include "day16.hpp"

#include "utils.hpp"

using day16::input_type;
using day16::output_type;
using day16::ticket_type;
using day16::valid_type;

ticket_type day16::find_all(std::vector<std::string> strng, std::regex rgx) {
  ticket_type output;

  for (auto &str : strng) {
    std::vector<int> interval;
    std::smatch sm;
    while (std::regex_search(str, sm, rgx)) {
      interval.push_back(std::stoi(sm[0]));
      str = sm.suffix();
    }
    output.push_back(interval);
  }
  return output;
}

input_type day16::transform_input(std::vector<std::string> &input) {
  input_type output;
  valid_type valid;
  ticket_type tickets;

  std::regex rgx_num("(\\d+)");

  for (auto &inp : input) {
    if (inp.find(" or ") != std::string::npos) {
      std::vector<std::string> leftright, name;
      utils::split_string(inp, " or ", leftright);
      utils::split_string(leftright[0], ":", name);
      valid[name[0]] = find_all(leftright, rgx_num);

    } else if (inp != "" && inp.find("ticket") == std::string::npos) {
      std::vector<int> split;
      utils::split_string(inp, ",", split);
      tickets.push_back(split);
    }
  }
  return std::make_pair(valid, tickets);
}

input_type day16::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

int day16::check(int digit, const valid_type &valid) {
  for (auto &mp : valid) {
    for (auto bounds = mp.second.begin(); bounds < mp.second.end(); bounds++) {
      if ((*bounds)[0] <= digit && digit <= (*bounds)[1]) {
        return -1;
      }
    }
  }
  return digit;
}

// Implement part one solution
output_type day16::solve_part1(const input_type &input_) {
  output_type error(0);

  for (auto &ticket : input_.second) {
    for (auto &nr : ticket) {
      auto val = check(nr, input_.first);
      error += (val != -1) ? val : 0;
    }
  }
  return error;
}

ticket_type day16::get_valid_tickets(const input_type &input_) {
  // Find any invalid ticket
  std::unordered_set<int> invalid_id;
  for (size_t id = 1; id < input_.second.size(); id++) {
    for (auto &nr : input_.second[id]) {
      if (check(nr, input_.first) != -1) {
        invalid_id.insert(id);
        break;
      }
    }
  }

  // Strip away the invalid tickets
  ticket_type output;
  for (size_t i = 0; i < input_.second.size(); i++) {
    if (!invalid_id.count(i)) {
      output.push_back(input_.second[i]);
    }
  }
  return output;
}

std::unordered_set<int> day16::get_valid_indices(
    std::string name, valid_type &valid, ticket_type &tickets,
    std::unordered_set<int> &indices) {
  // Get the needed lower and uper bounds for the field
  auto b1 = valid[name][0];
  auto b2 = valid[name][1];

  // Keep track of which indices are potential candidates for a field
  std::unordered_set<int> valid_idx;

  // Go through a row for all tickets
  for (size_t i = 0; i < tickets[0].size(); i++) {
    // If we have assigned this index, skip
    if (indices.count(i)) {
      continue;
    }
    // If an index in any ticket does not match requirements, skip
    bool not_break(true);
    for (size_t row = 0; row < tickets.size(); row++) {
      auto t = tickets[row][i];
      if (!((b1[0] <= t && t <= b1[1]) || (b2[0] <= t && t <= b2[1]))) {
        not_break = false;
        break;
      }
    }
    // If it did match all requirements, append it to list
    if (not_break) {
      valid_idx.insert(i);
      //  If we have found more than one match, skip this index
      if (valid_idx.size() > 1) {
        break;
      }
    }
  }
  return valid_idx;
}

std::unordered_map<std::string, int> day16::match_field_to_index(
    ticket_type &tickets, valid_type bounds) {
  // Keep track of which field belongs to which index
  std::unordered_map<std::string, int> ids;

  // Keep track of which indices we have assigned to classes
  std::unordered_set<int> indices;

  // Go through all fields once
  for (size_t field = 0; field < bounds.size(); field++) {
    // For each field, check how many indices we potentially match with
    for (auto &mp : bounds) {
      if (ids.count(mp.first)) {
        continue;
      }
      auto valid = get_valid_indices(mp.first, bounds, tickets, indices);
      // If we have found a unique match, we assign a field to this index
      if (valid.size() == 1) {
        ids[mp.first] = *(valid.begin());
        indices.insert(*(valid.begin()));
        break;
      }
    }
  }
  return ids;
}

// Implement part two solution
output_type day16::solve_part2(const input_type &input_) {
  // Get only valid tickets
  auto valid_tickets = get_valid_tickets(input_);
  // Get the corresponding field-to-index matches
  auto field_index = match_field_to_index(valid_tickets, input_.first);

  // Compute the puzzle output
  auto my_ticket = valid_tickets[0];
  int64_t prod(1);
  for (auto &mp : input_.first) {
    if (mp.first.find("departure") != std::string::npos) {
      prod *= my_ticket[field_index[mp.first]];
    }
  }
  return prod;
}
