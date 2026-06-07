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

    std::string number_representation_to_binary(std::string s, const char on, const char off) {
        // Turn each representation to strings
        std::string on_repr = std::string("") + on;
        std::string off_repr = std::string("") + off;

        // Remove starting zeroes
        while (s.size() > 1 && s[0] == '0') {
            s.erase(s.begin());
        }

        if (s == "0") { // If s is 0
            return off_repr;
        }

        std::string binary_representation = ""; // Initializes the variable

        /*
        We use the Division Method to divide the number by 2 repeatedly every time. It works like this:
            Do these following steps until your number reaches 0:
                Step 1: Divide the number by 2 and record its remainder
                Step 2: Push the recorded remainder at the front of the string
                Step 3: The number divided by 2 must be rounded down
        
        For example: convert 53 in binary
            1. 53 / 2 = 26 R1, current representation = 1
            2. 26 / 2 = 13 R0, current representation = 01
            3. 13 / 2 = 6 R1, current representation = 101
            4. 6 / 2 = 3 R0, current representation = 0101
            5. 3 / 2 = 1 R1, current representation = 10101
            6. 1 / 2 = 0 R1, current representation = 110101
        So 53 in base 10 is 110101 in base 2
        */

        // Repeat until s is "0"
        while (s != "0") {
            // Divides by 2 using long division
            std::string halved = "";
            bool carry = false;
            for (char c : s) {
                size_t digit_representation = c - '0' + (carry << 3) + (carry << 1); // Get the digit in integer form
                size_t half = digit_representation >> 1; // Get half of the number
                carry = digit_representation & 1; // Carry to the next number
                if (half != 0 || halved != "") {
                    halved += static_cast<char>(half + '0'); // Add the number to the result
                }
            }

            // At the end of the loop, carry represents the remainder of the number by 2
            if (carry) {
                binary_representation = on_repr + binary_representation;
            } else {
                binary_representation = off_repr + binary_representation;
            }

            if (halved == "") {
                halved = "0";
            }

            s = halved; // Sets s to halved
        }

        return binary_representation; // Our result is here
    }

    std::string replace(std::string s, const std::string replaced, const std::string into) {
        // Too complicated to explain...
        size_t start_pos = 0;
        while ((start_pos = s.find(replaced, start_pos)) != std::string::npos) {
            s.replace(start_pos, replaced.length(), into);
            start_pos += into.length();
        }

        return s; // Our result is here
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
}

void setup() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::freopen("input.INP", "r", stdin);
    std::freopen("output.OUT", "w", stdout);
}