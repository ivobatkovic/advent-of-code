#include "day21.hpp"

#include <boost/algorithm/string.hpp>

#include "utils.hpp"

using day21::input_type;
using day21::map_type;
using day21::match_type;
using day21::output_type1;
using day21::output_type2;
using day21::set_type;

input_type day21::transform_input(std::vector<std::string> &input) {
  input_type output;

  for (auto &inp : input) {
    // Split up the parts
    std::vector<std::string> split;
    utils::split_string(inp, "(contains ", split);

    // Remove white spaces around ingredients and the allergens
    std::string left(split[0]), right(split[1]);
    boost::algorithm::trim(left);
    boost::algorithm::trim(right);

    // Filter ingredients
    std::vector<std::string> ingredients;
    utils::split_string(left, " ", ingredients);

    // Filter allergens (and remove last parenthesis)
    right.erase(std::remove(right.begin(), right.end(), ' '), right.end());
    std::vector<std::string> allergens;
    utils::split_string(right.substr(0, right.length() - 1), ",", allergens);

    // Append them to the output
    output.push_back(std::make_pair(ingredients, allergens));
  }

  return output;
}

input_type day21::read_input(std::string file_name) {
  auto input = utils::read_file(file_name);
  return transform_input(input);
}

match_type day21::match_allergens(const input_type &input) {
  map_type possible_allergen;
  set_type all_ingredients;

  // Go through the list
  for (auto &[ingredients, allergens] : input) {
    // Record all ingredients we've seen
    set_type ingredients_set(ingredients.begin(), ingredients.end());
    all_ingredients.insert(ingredients_set.begin(), ingredients_set.end());

    // Go through each allergen
    for (auto allergen : allergens) {
      // If we haven't seen this allergen before, we know it can only be
      // produced by these ingredients
      if (!possible_allergen.count(allergen)) {
        possible_allergen[allergen] = ingredients_set;
        // Otherwise, only keep ingredients we've seen before
      } else {
        std::vector<std::string> o;
        std::set_intersection(possible_allergen[allergen].begin(),
                              possible_allergen[allergen].end(),
                              ingredients_set.begin(), ingredients_set.end(),
                              std::back_insert_iterator(o));
        possible_allergen[allergen] = set_type({o.begin(), o.end()});
      }
    }
  }
  // Returns a set of all ingredients, and which may cause allergies
  return match_type({all_ingredients, possible_allergen});
}

// Implement possible_allergenrt one solution
output_type1 day21::solve_part1(const input_type &input_) {
  auto [all_ing, poss_all] = match_allergens(input_);

  // Remove all ingredients that can cause an allergy
  for (auto &k : poss_all) {
    auto &ingreds = k.second;
    set_type diff;
    std::set_difference(all_ing.begin(), all_ing.end(), ingreds.begin(),
                        ingreds.end(), std::inserter(diff, diff.begin()));
    all_ing = diff;
  }

  // Go through the ingredients list and see how often the ingredients appear
  int s(0);
  for (auto &k : input_) {
    for (auto &ing : k.first) {
      if (all_ing.count(ing)) {
        s++;
      }
    }
  }
  return s;
}

// Implement part two solution
output_type2 day21::solve_part2(const input_type &input_) {
  auto possible_allergen = match_allergens(input_).second;

  // Keep going until we have matched as many ingredients as allergens
  map_type match;
  while (match.size() < possible_allergen.size()) {
    for (auto &kv : possible_allergen) {
      auto &allergy = kv.first;
      // If the allergy only has one ingredient, we match the ingredient
      if (possible_allergen[allergy].size() == 1) {
        std::string v = *possible_allergen[allergy].begin();
        match[allergy] = set_type({v});
        possible_allergen[allergy].erase(v);
        // If the allergy only has one ingredient, we match the ingredient
        for (auto &kv_ : possible_allergen) {
          auto &allergy_ = kv_.first;
          if (possible_allergen[allergy_].count(v)) {
            possible_allergen[allergy_].erase(v);
          }
        }
      }
    }
  }

  // Sort the allergens, and return the ingredients
  std::string msg;
  for (auto &k : match) {
    msg += *match[k.first].begin() + ",";
  }
  return msg.substr(0, msg.length() - 1);
}
