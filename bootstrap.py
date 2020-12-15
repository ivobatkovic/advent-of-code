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
        print(f"Fetched input year {year}, day {day}")
    except ReferenceError:
        data = ""
        print(f"Failed fetching input year {year}, day {day}")
    with open(dst, "r+") as f:
        f.write(data)


# Initialize python source file.
def setup_python_source(year, day):
    # Rename template_day.py
    src_files = [
        join(*[f"{year}",f"day{day}", "python", "day.py_tmp"]),
    ]
    dst_files = [
        join(*[f"{year}",f"day{day}", "python", f"day{day}.py"]),
    ]
    
    for src, dst in zip(src_files, dst_files):
        os.rename(src, dst)

    # Remove top line from template_day.py
    with open(dst_files[0], "r+") as f:
        data = f.readlines()[1:]
        f.truncate(0)
        f.seek(0)
        f.writelines(data)


# Initialize c++ build and source files
def setup_cpp_source(year, day):
    # Rename files
    src_files = [
        join(*[f"{year}",f"day{day}", "CMakeLists.txt_tmp"]),
        join(*[f"{year}",f"day{day}", "cpp", "include", "day.hpp_tmp"]),
        join(*[f"{year}",f"day{day}", "cpp", "src", "day.cpp_tmp"]),
        join(*[f"{year}",f"day{day}", "cpp", "src", "main.cpp_tmp"]),
        join(*[f"{year}",f"day{day}", "cpp", "src", "test.cpp_tmp"]),
    ]
    dst_files = [
        join(*[f"{year}",f"day{day}", "CMakeLists.txt"]),
        join(*[f"{year}",f"day{day}", "cpp", "include", f"day{day}.hpp"]),
        join(*[f"{year}",f"day{day}", "cpp", "src", f"day{day}.cpp"]),
        join(*[f"{year}",f"day{day}", "cpp", "src", "main.cpp"]),
        join(*[f"{year}",f"day{day}", "cpp", "src", "test.cpp"]),
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
        copytree("templates", join(f"{year}",f"day{day}"))
        print(f"Copied tree for {year} day{day}")

        # Copy python sources
        setup_python_source(year,day)
        print(f"Set up python structure for {year} day{day}")
        # Copy c++ sources
        setup_cpp_source(year,day)
        print(f"Set up c++ structure for {year} day{day}")

        # Done
        print(f"Completed setup for {year} day{day}")

    except OSError:
        print(f"Failed to create directory {year} day{day}")

    # Download latest data
    data_dst = join(*[f"{year}",f"day{day}", "data", "input.txt"])

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
