#include <chrono>
#include <iostream>

#include "cpp_utils.hpp"
#include "solutions.hpp"

using chrono_clock = std::chrono::high_resolution_clock;

int main() {
    const std::string input =
        utils::read_file_to_string("2019/day1/data/input.txt");

    auto begin = chrono_clock::now();
    const auto part_one = day1::solve_part1(input);
    auto end = chrono_clock::now();
    auto duration = std::chrono::duration<double>(end - begin).count() * 1e3;
    printf("Solution to part one: %s (time taken %.2f [ms])\n",
           part_one.c_str(), duration);

    begin = chrono_clock::now();
    const auto part_two = day1::solve_part2(input);
    end = chrono_clock::now();
    duration = std::chrono::duration<double>(end - begin).count() * 1e3;
    printf("Solution to part two: %s (time taken %.2f [ms])\n",
           part_two.c_str(), duration);

    return 0;
}
