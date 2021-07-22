#include "2019/day7/cpp/include/amplifier.hpp"

#include <algorithm>
#include <vector>

#include "2019/day5/cpp/include/intcode.hpp"

Amplifier::Amplifier() {}

// Go through all phase permutations to find maximum thrust
int Amplifier::get_maximum_thrust(std::string file_name) {
  // Default max value
  auto max_val = -INT8_MAX;

  int phases[] = {0, 1, 2, 3, 4};

  // Temporary output value for a phase
  int out;
  do {
    out = 0;
    for (auto &i : phases) {
      Intcode intcode = Intcode(file_name, {i}, true, false);
      auto output = intcode(out);
      out = std::get<1>(output);
      max_val = (out > max_val) ? out : max_val;
    }
  } while (std::next_permutation(phases, phases + 5));

  return max_val;
}

// Similar to above, but goes through a phase until the program completes
int Amplifier::feedback_thrust(std::string file_name) {
  // Temporary value
  auto max_val(-INT8_MAX);

  // Phases
  int phases[] = {5, 6, 7, 8, 9};
  do {
    // Populate intcode vector for a given phase
    std::vector<Intcode> intcodes;
    for (auto &i : phases) {
      intcodes.push_back(Intcode(file_name, {i}, false, false));
    }

    // Keep going until the feedback loop terminates
    bool terminated = false;
    int out = 0;
    while (!terminated) {
      for (auto &intcode : intcodes) {
        auto output = intcode(out);
        terminated = std::get<0>(output);
        out = std::get<1>(output);
      }
    }
    max_val = (out > max_val) ? out : max_val;

  } while (std::next_permutation(phases, phases + 5));
  return max_val;
}
