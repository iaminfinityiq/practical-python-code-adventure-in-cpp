#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

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
     * This is used in Challenge #1 Part 1
     */
    std::vector<std::string> split(const std::string &s, const char delimeter = ' ');
}

namespace utf8 {
    /**
     * Converts an UTF8 string (on std::string) to a `std::u32string`
     * 
     * @param s input string
     * @return The `std::u32string`
     * 
     * This is used in Challenge #1 Part 1 and Challenge #1 Part 2
     */
    std::u32string utf8_to_u32(const std::string &s);

    /**
     * Takes in input as a line and returns the `std::u32string`
     * 
     * @return The input line in `std::u32string`
     * 
     * This is used in Challenge #1 Part 2
     */
    std::u32string input_getline();
}

/**
 * Setups each main.cpp file used in each exercise
 */
void setup();