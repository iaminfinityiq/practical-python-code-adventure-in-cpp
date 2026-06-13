#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdint>

using unicode_char = char32_t;
using char_t = unsigned char;

namespace string {
    /**
     * Splits the string into words separated by the delimiter.
     *
     * @param s input string
     * @param delimeter character used to split (default space)
     * @return A list of words
     * 
     * This is used in Challenge #1 Part 1, Challenge #1 Part 2, Challenge #2 Part 1 and Challenge #2 Part 2
     */
    std::vector<std::string> split(const std::string &s, const char delimeter = ' ');

    /**
     * Turns a number represented by string to a string that converts to binary
     * 
     * @param s input number
     * @param on character that represents the digit 1
     * @param off character that represents the digit 0
     * @return The binary representation as a string
     * 
     * This is used in Challenge #1 Part 2
     */
    std::string number_representation_to_binary(std::string s, const char on = '1', const char off = '0');

    /**
     * Replaces all instances of a string to another string
     * 
     * @param s input string
     * @param replaced string that gets replaced
     * @param into string that replaces each instance of `replaced`
     * 
     * This is used in Challenge #1 Part 2
     */
    std::string replace(std::string s, const std::string replaced, const std::string into);
};

namespace utf8 {
    /**
     * Converts an UTF8 string (on std::string) to a `std::u32string`
     * 
     * @param s input string
     * @return The `std::u32string`
     * 
     * This is used in Challenge #1 Part 2
     */
    std::u32string utf8_to_u32(const std::string &s);
}

/**
 * Setups each main.cpp file used in each exercise
 */
void setup();