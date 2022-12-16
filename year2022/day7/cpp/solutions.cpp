#include "year2022/day7/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day7 {

Directory::Directory(std::string parent) : parent_{parent}, size_{0U} {}
void Directory::add_file(std::string size, std::string name) {
    files_.push_back({size, name});
}
void Directory::Directory::add_subdirectory(std::string dir) {
    subdirectories_.push_back(dir);
}

FileSystem::FileSystem(std::vector<std::string> const &inp)
    : dirs_(create_tree(inp)) {
    compute_size();
}

std::unordered_map<std::string, std::unique_ptr<Directory>>
FileSystem::create_tree(std::vector<std::string> const &inp) {
    std::unordered_map<std::string, std::unique_ptr<Directory>> dirs;

    std::string cwd = "", parent = "";
    for (auto &row : inp) {
        if ("$ cd" == row.substr(0, 4)) {
            if ('/' == row[5]) {
                parent = "";
                cwd = "/";
            } else if (".." == row.substr(5, 2)) {
                cwd = parent;
                parent = dirs[cwd]->parent_;
            } else {
                parent = cwd;
                cwd += row.substr(5, row.size() - 5) + "/";
            }
        } else if ("$ ls" == row.substr(0, 4)) {
            continue;
        } else {
            if (!dirs.count(cwd)) {
                dirs[cwd] = std::make_unique<Directory>(Directory(parent));
            }
            auto split = utils::split_string<std::string>(row, " ");
            if ("dir" == split[0]) {
                dirs[cwd]->add_subdirectory(split[1]);
            } else {
                dirs[cwd]->add_file(split[0], split[1]);
            }
        }
    }
    return dirs;
}

void FileSystem::compute_size(std::string name) {
    for (auto &directory : dirs_[name]->subdirectories_) {
        compute_size(name + directory + "/");
        dirs_[name]->size_ += dirs_[name + directory + "/"]->size_;
    }
    for (auto &[size, _] : dirs_[name]->files_) {
        dirs_[name]->size_ += std::stoul(size);
    }
}

using input_type = FileSystem;

static input_type transform_input(const std::string &input_string) {
    return FileSystem(utils::split_string<std::string>(input_string, "\n"));
}

std::string solve_part1(const std::string &input_string) {
    auto input = transform_input(input_string);

    std::vector<size_t> results{};
    for (auto const &[key, val] : input.dirs_) {
        if (val->size_ < 100000U) {
            results.push_back(val->size_);
        }
    }
    return std::to_string(std::accumulate(results.begin(), results.end(), 0));
}

std::string solve_part2(const std::string &input_string) {
    auto input = transform_input(input_string);
    size_t disk_space = 70000000;
    size_t space_needed = 30000000;

    std::vector<size_t> results{};
    for (auto const &[key, val] : input.dirs_) {
        if (val->size_ > input.dirs_["/"]->size_ + space_needed - disk_space) {
            results.push_back(val->size_);
        }
    }
    return std::to_string(*std::min_element(results.begin(), results.end()));
}

}  // namespace day7

}  // namespace year2022
