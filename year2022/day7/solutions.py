#!/usr/bin/env python3
import argparse
import pytest
import time


class Directory:
    def __init__(self, parent):
        self.parent_ = parent
        self.files_ = []
        self.subdirectories_ = []
        self.size_ = 0

    def add_file(self, name, size):
        self.files_.append((name, size))

    def add_subdirectory(self, directory_name):
        self.subdirectories_.append(directory_name)


class FileSystem:
    def __init__(self, inp):
        self.dirs_ = self.create_tree(inp)
        self.compute_size("/")

    def create_tree(self, inp):
        dirs = dict()

        cwd, parent = "", ""
        for row in inp:
            if "$ cd" in row:
                if "/" in row:
                    parent = None
                    cwd = "/"
                elif ".." in row:
                    cwd = parent
                    parent = dirs[cwd].parent_
                else:
                    parent = cwd
                    cwd += row[5:] + "/"
            elif "$ ls" in row:
                continue
            else:
                if cwd not in dirs:
                    dirs[cwd] = Directory(parent)
                if "dir" in row:
                    dirs[cwd].add_subdirectory(row[4:])
                else:
                    size, name = row.split()
                    dirs[cwd].add_file(size, name)
        return dirs

    def compute_size(self, name):
        for directory in self.dirs_[name].subdirectories_:
            self.compute_size(name + directory + "/")
            self.dirs_[name].size_ += self.dirs_[name + directory + "/"].size_
        for size, _ in self.dirs_[name].files_:
            self.dirs_[name].size_ += int(size)


def transform_input(input_):
    return FileSystem(input_.splitlines())


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return sum(
        inp.dirs_[x].size_
        for x in inp.dirs_.keys()
        if inp.dirs_[x].size_ < 1e5
    )


def solve_part2(input_):
    tree = transform_input(input_)
    disk_space = 7e7
    space_needed = 3e7
    return min(
        tree.dirs_[x].size_
        for x in tree.dirs_.keys()
        if tree.dirs_[x].size_
        > tree.dirs_["/"].size_ + space_needed - disk_space
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 7")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day7/data/input.txt",
        nargs="?",
        help="Path to data file",
    )
    return parser.parse_args()


def main():
    parser = parse_args()
    input_ = read_input(parser.file_name)

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1:.2f}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2:.2f}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("year2022/day7/data/test_input0.txt", 95437)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day7/data/test_input0.txt", 24933642)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
