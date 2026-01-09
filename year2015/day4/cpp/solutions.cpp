#include "year2015/day4/cpp/solutions.hpp"

#include <openssl/md5.h>

#include <string>

namespace year2015 {

namespace day4 {

using namespace std;
using input_type = string;

static input_type transform_input(const string &input_string) {
    return input_string;
}

bool check_md5(string const &data, bool const part_two = false) {
    // Could use openssl/evp.h instead but it's too clunky compared to this
    unsigned char digest[MD5_DIGEST_LENGTH];
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    MD5(reinterpret_cast<const unsigned char *>(data.c_str()), data.size(),
        digest);
#pragma GCC diagnostic pop

    return (!part_two) ? (digest[0] == 0 && digest[1] == 0 &&
                          (digest[2] & 0b11110000) == 0)
                       : (digest[0] == 0 && digest[1] == 0 && digest[2] == 0);
}

std::string solve_part1(const string &input_string, int32_t num) {
    auto key = transform_input(input_string);

    while (true) {
        string data = key + to_string(num);

        if (check_md5(data)) {
            return to_string(num);
        }
        num++;
    }
    return "0";
}

std::string solve_part2(const string &input_string, int32_t num) {
    auto key = transform_input(input_string);
    while (true) {
        string data = key + to_string(num);

        if (check_md5(data, true)) {
            return to_string(num);
        }
        num++;
    }
    return "0";
}

}  // namespace day4

}  // namespace year2015
