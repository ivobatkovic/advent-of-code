#include <chrono>
#include <iostream>
#include <string>

#include "utils/cpp_utils.hpp"
#include "year2022/day7/cpp/solutions.hpp"

using chrono_clock = std::chrono::high_resolution_clock;

int main(int argc, char** argv) {
    std::string file_name =
        (argc > 1) ? std::string(argv[1]) : "year2022/day7/data/input.txt";
    const std::string input = utils::read_file_to_string(file_name);

    auto begin = chrono_clock::now();
    const auto part_one = year2022::day7::solve_part1(input);
    auto end = chrono_clock::now();
    auto duration = std::chrono::duration<double>(end - begin).count() * 1e3;
    printf("Solution to part one: %s (time taken %.2f [ms])\n",
           part_one.c_str(), duration);

    begin = chrono_clock::now();
    const auto part_two = year2022::day7::solve_part2(input);
    end = chrono_clock::now();
    duration = std::chrono::duration<double>(end - begin).count() * 1e3;
    printf("Solution to part two: %s (time taken %.2f [ms])\n",
           part_two.c_str(), duration);

    return 0;
}
