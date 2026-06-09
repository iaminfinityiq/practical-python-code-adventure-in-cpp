#include "helpers.hpp"

namespace string {
    std::vector<std::string> split(const std::string &s, const char delimeter) {
        // Initializes the variables
        std::vector<std::string> tokens = {};
        std::string current_token = {};
        
        for (char c : s + delimeter) { // Loops each character in s + delimeter (important reason)
            if (c == delimeter) { // Checks for a delimeter
                if (current_token != "") {
                    tokens.push_back(current_token); // Token is not empty, then add the token
                    current_token = ""; // Resets the token
                }
            } else {
                current_token += c; // Adds the character to the token
            }
        }

        return tokens; // Our result is here
    }
}

namespace utf8 {
    std::u32string utf8_to_u32(const std::string &s) {
        // Too complicated to explain...
        std::u32string result;
        for (size_t i = 0; i < s.size();) {
            char_t c = static_cast<char_t>(s[i]);

            if ((c & 0x80) == 0) {
                result.push_back(c);
                i++;
            }
            else if ((c & 0xE0) == 0xC0) {
                unicode_char cp =
                    ((c & 0x1F) << 6) |
                    (static_cast<char_t>(s[i + 1]) & 0x3F);
                result.push_back(cp);
                i += 2;
            }
            else if ((c & 0xF0) == 0xE0) {
                unicode_char cp =
                    ((c & 0x0F) << 12) |
                    ((static_cast<char_t>(s[i + 1]) & 0x3F) << 6) |
                    (static_cast<char_t>(s[i + 2]) & 0x3F);
                result.push_back(cp);
                i += 3;
            }
            else if ((c & 0xF8) == 0xF0) {
                unicode_char cp =
                    ((c & 0x07) << 18) |
                    ((static_cast<char_t>(s[i + 1]) & 0x3F) << 12) |
                    ((static_cast<char_t>(s[i + 2]) & 0x3F) << 6) |
                    (static_cast<char_t>(s[i + 3]) & 0x3F);
                result.push_back(cp);
                i += 4;
            }
        }

        return result; // Our result is here
    }

    std::u32string input_getline() {
        std::string input; // Initializes the input variable as std::string
        std::getline(std::cin, input); // Gets the line input
        std::u32string returned = utf8_to_u32(input); // Converts the input line to `std::u32string`
        return returned;
    }
}

void setup() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::freopen("input.INP", "r", stdin);
    std::freopen("output.OUT", "w", stdout);
}