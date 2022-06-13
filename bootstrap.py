#!/usr/bin/env python3
""" Credit: code taken and modified from https://github.com/amrit110/aoc """
import argparse
import os
from os.path import join
from shutil import copytree
from aocd import get_data


def download_data(year, day, dst):
    try:
        data = get_data(year=year, day=day)
        print(f"Fetched input year year{year}, day {day}")
    except ReferenceError:
        data = ""
        print(f"Failed fetching input year year{year}, day {day}")
    with open(dst, "r+") as f:
        f.write(data)


# Initialize python source file.
def setup_python_source(year, day):
    # Rename template_day.py
    src_files = [
        join(*[f"year{year}",f"day{day}", "solutions.py_tmp"]),
        join(*[f"year{year}",f"day{day}", "__init__.py_tmp"]),
    ]
    dst_files = [
        join(*[f"year{year}",f"day{day}", f"solutions.py"]),
         join(*[f"year{year}",f"day{day}", f"__init__.py"]),
    ]
    
    for src, dst in zip(src_files, dst_files):
        os.rename(src, dst)

    # Remove top line from template_day.py
    with open(dst_files[0], "r+") as f:
        lines = f.read().splitlines()[1:]
        # Reset file cursor
        f.seek(0)
        f.truncate(0)
        for line in lines:
            f.write(eval("f'{}'".format(line)) + "\n")


# Initialize c/c++ build and source files
def setup_cpp_source(year, day):
    # Rename files
    src_files = [
        join(*[f"year{year}",f"day{day}", "CMakeLists.txt_tmp"]),
        join(*[f"year{year}",f"day{day}", "BUILD.bazel_tmp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "include", "solutions.hpp_tmp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "solutions.cpp_tmp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "main.cpp_tmp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "test.cpp_tmp"]),
        join(*[f"year{year}",f"day{day}", "c", "include", "solutions.h_tmp"]),
        join(*[f"year{year}",f"day{day}", "c", "solutions.c_tmp"]),
        join(*[f"year{year}",f"day{day}", "c", "main.c_tmp"]),
        join(*[f"year{year}",f"day{day}", "c", "test.cpp_tmp"]),
    ]
    dst_files = [
        join(*[f"year{year}",f"day{day}", "CMakeLists.txt"]),
        join(*[f"year{year}",f"day{day}", "BUILD.bazel"]),
        join(*[f"year{year}",f"day{day}", "cpp", "include", "solutions.hpp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "solutions.cpp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "main.cpp"]),
        join(*[f"year{year}",f"day{day}", "cpp", "test.cpp"]),
        join(*[f"year{year}",f"day{day}", "c", "include", "solutions.h"]),
        join(*[f"year{year}",f"day{day}", "c", "solutions.c"]),
        join(*[f"year{year}",f"day{day}", "c", "main.c"]),
        join(*[f"year{year}",f"day{day}", "c", "test.cpp"]),
    ]
    for src, dst in zip(src_files, dst_files):
        os.rename(src, dst)

    # Update files with the corresponding day
    for dst in dst_files:
        with open(dst, "r+") as f:
            lines = f.read().splitlines()
            # Reset file cursor
            f.seek(0)
            f.truncate(0)
            for line in lines:
                f.write(eval("f'{}'".format(line)) + "\n")


def parse_args():
    parser = argparse.ArgumentParser(description="Bootstrap")
    parser.add_argument("-d", "--day", required=True, type=int, help="day")
    parser.add_argument("-y", "--year", required=True, type=int, help="year")
    parser.add_argument("-i", "--input", type=int, default=0, help="input")

    return parser.parse_args()


def bootstrap_solution(year, day, download_input):
    # Try to make directories
    try:
        
        # Copy templates folder
        copytree("templates", join(f"year{year}",f"day{day}"))
        print(f"Copied tree for year{year} day{day}")

        # Copy python sources
        setup_python_source(year,day)
        print(f"Set up python structure for year{year} day{day}")
        # Copy c++ sources
        setup_cpp_source(year,day)
        print(f"Set up c/c++ structure for year{year} day{day}")

        # Done
        print(f"Completed setup for year{year} day{day}")

    except OSError:
        print(f"Failed to create directory year{year} day{day}")

    # Download latest data
    data_dst = join(*[f"year{year}",f"day{day}", "data", "input.txt"])

    if download_input:
        download_data(year, day, data_dst)


def main():
    args = parse_args()
    day = args.day
    year = args.year
    download_input = args.input
    bootstrap_solution(year,day,download_input)


if __name__ == "__main__":
    main()
