#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day

    ingredients_list, allergens_list = [], []
    for inp in input_.splitlines():

        # Split up the parts
        ingredients, allergens = inp.split("(contains ")

        # Remove white spaces around ingredients and the allergens
        ingredients = ingredients.split()
        allergens = allergens[:-1].replace(" ", "").split(",")

        # Append them to the list
        ingredients_list.append(ingredients)
        allergens_list.append(allergens)

    return [ingredients_list, allergens_list]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def match_allergens(input_):

    ingredients_list, allergens_list = input_

    possible_allergen = dict()
    all_ingredients = set()

    # Go through the list
    for allergens, ingredients in zip(allergens_list, ingredients_list):

        # Record all ingredients we've seen
        all_ingredients |= set(ingredients)

        # Go through each allergen
        for allergen in allergens:
            # If we haven't seen this allergen before, we know it can only be
            # produced by this ingredients
            if allergen not in possible_allergen:
                possible_allergen[allergen] = set(ingredients)
            # Otherwise, only keep ingredients we've seen before
            else:
                possible_allergen[allergen] = possible_allergen[
                    allergen
                ].intersection(ingredients)
    # Returns a set of all ingredients, and which may cause allergies
    return all_ingredients, possible_allergen


def solve_part1(input_):

    all_ingredients, possible_allergen = match_allergens(input_)

    # Remove all ingredients that can cause an allergy
    for ingredients in possible_allergen.values():
        all_ingredients -= ingredients

    # Go through the ingredients list and see how often the ingredients appear
    return sum(
        [
            1
            for ingredients in input_[0]
            for ingredient in ingredients
            if ingredient in all_ingredients
        ]
    )


def solve_part2(input_):

    all_ingredients, possible_allergen = match_allergens(input_)

    match = dict()
    # Keep going until we have matched as many ingredients as allergens
    while len(match) < len(possible_allergen):
        for allergy in possible_allergen:
            # If the allergy only has one ingredient, we match the ingredient
            if len(possible_allergen[allergy]) == 1:
                match[allergy] = possible_allergen[allergy].pop()
                # Remove the ingredient from the other possible reactions
                for allergy_ in possible_allergen:
                    if match[allergy] in possible_allergen[allergy_]:
                        possible_allergen[allergy_].remove(match[allergy])

    return "".join(
        [match[key] + "," for key in sorted(list(possible_allergen.keys()))]
    )[:-1]


def main():
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1, output1", [("../data/test_input0.txt", 5)])
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("../data/test_input0.txt", "mxmxvkd,sqjhc,fvjkl")]
)
def test2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
