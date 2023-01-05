#ifndef _YEAR2022_DAY7_CPP_H_
#define _YEAR2022_DAY7_CPP_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace year2022 {

namespace day7 {

class Directory {
   public:
    Directory(std::string parent);
    void add_file(std::string const size, std::string const name);
    void add_subdirectory(std::string const name);
    std::string parent_;
    std::size_t size_;
    std::vector<std::pair<std::string, std::string>> files_{};
    std::vector<std::string> subdirectories_{};
};

class FileSystem {
   public:
    FileSystem(std::vector<std::string> const &inp);
    std::unordered_map<std::string, std::unique_ptr<Directory>> dirs_;

   private:
    std::unordered_map<std::string, std::unique_ptr<Directory>> create_tree(
        std::vector<std::string> const &inp);
    void compute_size(std::string name = "/");
};

std::string solve_part1(const std::string &input_string);

std::string solve_part2(const std::string &input_string);

}  // namespace day7

}  // namespace year2022

#endif
