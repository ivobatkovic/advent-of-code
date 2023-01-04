#include "year2022/day7/cpp/solutions.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/cpp_utils.hpp"

namespace year2022 {

namespace day7 {

using namespace std;
using input_type = FileSystem;

Directory::Directory(string parent) : parent_{parent}, size_{0U} {}
void Directory::add_file(string size, string name) {
    files_.push_back({size, name});
}
void Directory::Directory::add_subdirectory(string dir) {
    subdirectories_.push_back(dir);
}

FileSystem::FileSystem(vector<string> const &inp) : dirs_(create_tree(inp)) {
    compute_size();
}

unordered_map<string, unique_ptr<Directory>> FileSystem::create_tree(
    vector<string> const &inp) {
    unordered_map<string, unique_ptr<Directory>> dirs;

    string cwd = "", parent = "";
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
                dirs[cwd] = make_unique<Directory>(Directory(parent));
            }
            auto split = utils::split_string<string>(row, " ");
            if ("dir" == split[0]) {
                dirs[cwd]->add_subdirectory(split[1]);
            } else {
                dirs[cwd]->add_file(split[0], split[1]);
            }
        }
    }
    return dirs;
}

void FileSystem::compute_size(string name) {
    for (auto &directory : dirs_[name]->subdirectories_) {
        compute_size(name + directory + "/");
        dirs_[name]->size_ += dirs_[name + directory + "/"]->size_;
    }
    for (auto &[size, _] : dirs_[name]->files_) {
        dirs_[name]->size_ += stoul(size);
    }
}

static input_type transform_input(const string &input_string) {
    return FileSystem(utils::split_string<string>(input_string, "\n"));
}

string solve_part1(const string &input_string) {
    auto input = transform_input(input_string);

    vector<size_t> results{};
    for (auto const &[key, val] : input.dirs_) {
        if (val->size_ < 100000U) {
            results.push_back(val->size_);
        }
    }
    return to_string(accumulate(results.begin(), results.end(), 0));
}

string solve_part2(const string &input_string) {
    auto input = transform_input(input_string);
    size_t disk_space = 70000000;
    size_t space_needed = 30000000;

    vector<size_t> results{};
    for (auto const &[key, val] : input.dirs_) {
        if (val->size_ > input.dirs_["/"]->size_ + space_needed - disk_space) {
            results.push_back(val->size_);
        }
    }
    return to_string(*min_element(results.begin(), results.end()));
}

}  // namespace day7

}  // namespace year2022
