#include "year2016/day5/cpp/solutions.hpp"

#include <openssl/md5.h>

#include <string>

namespace year2016 {

namespace day5 {

using namespace std;
using input_type = string;

static input_type transform_input(const string &input_string) {
    return input_string;
}

std::string to_hex(const unsigned char *digest) {
    static const char *hex_chars = "0123456789abcdef";
    std::string hex;
    hex.resize(MD5_DIGEST_LENGTH * 2);

    for (size_t i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hex[2 * i] = hex_chars[(digest[i] >> 4) & 0xF];
        hex[2 * i + 1] = hex_chars[(digest[i]) & 0xF];
    }
    return hex;
}

bool check_md5(string const &data, unsigned char digest[MD5_DIGEST_LENGTH]) {
    // Could use openssl/evp.h instead but it's too clunky compared to this
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    MD5(reinterpret_cast<const unsigned char *>(data.c_str()), data.size(),
        digest);
#pragma GCC diagnostic pop

    return (digest[0] == 0 && digest[1] == 0 && (digest[2] & 0b11110000) == 0);
}

std::string solve_part1(const string &input_string, int32_t num,
                        size_t const num_iterations) {
    auto key = transform_input(input_string);

    string output = "";
    unsigned char digest[MD5_DIGEST_LENGTH];

    for (size_t i{0U}; i < num_iterations; ++i) {
        while (true) {
            if (check_md5(key + to_string(++num), digest)) {
                string const hex_hash = to_hex(digest);

                output += hex_hash.at(5U);
                break;
            }
        }
    }
    return output;
}

std::string solve_part2(const string &input_string, int32_t num,
                        size_t const num_iterations) {
    auto key = transform_input(input_string);

    string output = "________";
    size_t iterations{0U};
    unsigned char digest[MD5_DIGEST_LENGTH];

    while (true) {
        if (check_md5(key + to_string(++num), digest)) {
            string const hash_hex = to_hex(digest);
            size_t const idx = static_cast<size_t>(hash_hex[5U] - '0');
            if (idx < 8U && output.at(idx) == '_') {
                output.at(idx) = hash_hex[6U];
                if (++iterations == num_iterations) {
                    break;
                }
            }
        }
    }

    return output;
}

}  // namespace day5

}  // namespace year2016
