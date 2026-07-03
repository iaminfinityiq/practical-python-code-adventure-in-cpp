#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using unicode_char = char32_t;
using char_t = unsigned char;

// Namespace for string manipulations
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

    /**
     * Replaces each character that matches the target character with a string
     * 
     * @param s input string
     * @param target the target character
     * @param replaced the string replacing the target character
     * @return The new string
     * 
     * This is used in Challenge #3 Part 1 and Challenge #3 Part 2
     */
    std::string replace(const std::string &s, const char target, const std::string replaced);
}

// Namespace for UTF8 string manipulations
namespace utf8 {
    /**
     * Converts an UTF8 string (on std::string) to a `std::u32string`
     * 
     * @param s input string
     * @return The `std::u32string`
     * 
     * This is used in Challenge #1 Part 1
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

// Namespace for the fraction object
namespace fraction {
    /*
    A struct for storing fractions, mainly because I'm scared of decimal precision

    This is used in Challenge #4 Part 1
    */
    struct Fraction {
        bool is_negative;
        size_t numerator;
        size_t denominator;

        /**
         * Fraction initializer
         * 
         * @param is_negative the sign of the fraction, can be positive or negative
         * @param numerator the numerator of the fraction
         * @param denominator the denominator of the fraction
         * @return Nothing :)
         * 
         * This is used in Challenge #4 Part 1
         */
        Fraction(const bool is_negative, const size_t numerator, const size_t denominator);
        
        /**
         * Checks if the fraction is 0
         * @return true if the fraction is 0 else false
         */
        bool zero();

        /**
         * Simplifies the fraction by manipulating the numerator and denominator attributes
         * @return Nothing :)
         */
        void simplify();

        /**
         * Negates the fraction by manipulating the sign attributes
         * @return Nothing :)
         */
        void negate();

        /**
         * Flips the fraction into their reciprocal
         * @return Nothing :)
         */
        void reciprocal();

        /**
         * Finds the ceiling of the function
         * @return The ceiling of the fraction, or 0 if the function is negative
         */
        size_t ceil();

        /**
         * Checks if the fraction is an integer
         * @return true if the fraction is an integer else false
         * 
         * This is used in Challenge #4 Part 1
         */
        bool is_integer();
    };

    /**
     * Adds 2 fractions and simplify them
     * 
     * @param a the first fraction
     * @param b the second fraction
     * @return The result
     * 
     * This is used in Challenge #4 Part 1
     */
    Fraction add(Fraction a, Fraction b);

    /**
     * Subtracts 2 fractions and simplify them
     * 
     * @param a the first fraction
     * @param b the second fraction
     * @return The result
     */
    Fraction subtract(Fraction a, Fraction b);

    /**
     * Multiplies 2 fractions and simplify them
     * 
     * @param a the first fraction
     * @param b the second fraction
     * @return The result
     */
    Fraction multiply(Fraction a, Fraction b);

    /**
     * Divides 2 fractions and simplify them
     * 
     * @param a the first fraction
     * @param b the second fraction
     * @return The result
     * 
     * This is used in Challenge #4 Part 1
     */
    Fraction divide(Fraction a, Fraction b);

    /**
     * Turns an unsigned integer to a fraction
     * 
     * @param n the unsigned integer needed to convert
     * @return The result
     * 
     * This is used in Challenge #4 Part 1
     */
    Fraction whole_to_fraction(const size_t n);

    /**
     * 0
     * @return 0
     * 
     * This is used in Challenge #4 Part 1
     */
    const Fraction ZERO = whole_to_fraction(0);
}

/**
 * Setups each main.cpp file used in each exercise
 */
void setup();