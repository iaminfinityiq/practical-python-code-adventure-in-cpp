#include "helpers.hpp"
#include <numeric>

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

    std::string replace(const std::string &s, const char target, const std::string replaced) {
        std::string returned = ""; // Initializes the result variable
        for (char c : s) { // Loops through each character of the original string
            if (target == c) {
                returned += replaced; // If the character matches the target, we insert the replaced string instead
            } else {
                returned += c; // Appends the string like normal
            }
        }

        return returned; // Our result is here
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

namespace fraction {
    Fraction::Fraction(const bool is_negative, const size_t numerator, const size_t denominator) {
        // Initializes the attributes
        this->is_negative = is_negative;
        this->numerator = numerator;
        this->denominator = denominator;
    }

    bool Fraction::zero() {
        return this->numerator == 0; // A fraction can only be 0 if the numerator is 0
    }

    void Fraction::simplify() {
        // If the fraction is 0, set the sign to false and set the denominator to 1
        if (this->zero()) {
            this->is_negative = false;
            this->denominator = 1;
            return;
        }

        // If the numerator or denominator is 1 then there is no need to simplify
        if (this->numerator == 1 || this->denominator == 1) {
            return;
        }

        /*
        If the difference between the numerator and denominator is 1 then there also is no need to simplify
        Basic proof:
            Let the numerator be n and denominator be d (note that n and d are unsigned in this definition of fractions)
            Then let g be gcd(n, d)
            Now we have g | n and g | d => g | n-d

            Case 1: n = d+1 so n-d = 1 which means g | 1 or g = 1
            Case 2: d = n+1 so n-d = -1 which means g | -1 or g = 1
        */
        if (this->numerator == this->denominator + 1 || this->denominator == this->numerator + 1) {
            return;
        }

        size_t gcd = std::gcd(this->numerator, this->denominator); // Get the gcd of the numerator and denominator
        this->numerator /= gcd; // Divide both sides of numerator by the gcd
        this->denominator /= gcd; // Divide both sides of the denominator by the gcd
    }

    void Fraction::negate() {
        this->simplify(); // Simplify the fraction
        if (this->zero()) {
            return; // If the number is 0 then don't do anything
        }

        this->is_negative = !this->is_negative; // Flip the sign
    }

    void Fraction::reciprocal() {
        this->simplify(); // Simplify the fraction
        size_t temp = this->numerator; // Stores the numerator in a temporary variable

        // Flips the fraction
        this->numerator = this->denominator;
        this->denominator = temp;
    }

    size_t Fraction::ceil() {
        this->simplify(); // Simplifies the fraction
        if (this->is_negative) {
            // If the fraction is negative then return 0
            return 0; // Our result is here
        }

        if (this->denominator == 1) {
            // If the numerator can be divided cleanly using the denominator, the result is the numerator
            return this->numerator; // Our result is here
        }

        size_t whole = this->numerator / this->denominator; // Divides the numerator by the denominator to get the whole part
        return whole + 1; // Our result is here
    }

    bool Fraction::is_integer() {
        this->simplify(); // Simplifies the fraction
        return this->denominator == 1; // Our result is here
    }

    Fraction add(Fraction a, Fraction b) {
        // Simplify the 2 fractions
        a.simplify();
        b.simplify();

        size_t common_denominator = std::lcm(a.denominator, b.denominator); // Find the common denominator 
        size_t numerator_a = common_denominator/a.denominator*a.numerator; // Find the numerator for a with the common denominator
        size_t numerator_b = common_denominator/b.denominator*b.numerator; // Find the numerator for b with the common denominator
        if (a.is_negative == b.is_negative) { // If the signs are equal
            size_t numerator = numerator_a + numerator_b; // Add the 2 values of the numerator
            Fraction result = Fraction(a.is_negative, numerator, common_denominator); // Store in a fraction
            result.simplify(); // Simplify
            return result; // Our result is here
        }

        if (numerator_a == numerator_b) { // If 2 numerators cancel each other
            return Fraction(false, 0, 1); // Returns 0
        }

        if (numerator_a > numerator_b) { // If numerator for a is greater than numerator for b
            size_t numerator = numerator_a - numerator_b; // Subtract the 2 values
            Fraction result = Fraction(a.is_negative, numerator, common_denominator); // Stores the result with the sign of fraction a
            result.simplify(); // Simplify
            return result; // Our result is here
        }

        // If numerator for a is smaller than numerator for b
        size_t numerator = numerator_b - numerator_a; // Subtract the 2 values
        Fraction result = Fraction(b.is_negative, numerator, common_denominator); // Stores the result with the sign of fraction b
        result.simplify(); // Simplify
        return result; // Our result is here
    }

    Fraction subtract(Fraction a, Fraction b) {
        b.negate(); // Negate b
        return add(a, b); // Our result is here
    }

    Fraction multiply(Fraction a, Fraction b) {
        // Simplify the 2 fractions
        a.simplify();
        b.simplify();

        bool is_negative = a.is_negative != b.is_negative; // Determine if the new sign should be negative or not
        size_t numerator = a.numerator*b.numerator; // Multiply the 2 numerators for the new numerator
        size_t denominator = a.denominator*b.denominator; // Multiply the 2 denominators for the new denominator

        Fraction result = Fraction(is_negative, numerator, denominator); // Store the result in a fraction
        result.simplify(); // Simplify
        return result; // Our result is here
    }

    Fraction divide(Fraction a, Fraction b) {
        b.reciprocal(); // Flip the numerator and denominator
        return multiply(a, b); // Our result is here
    }

    Fraction whole_to_fraction(const size_t n) {
        return Fraction(false, n, 1); // Our result is here
    }
}

void setup() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::freopen("input.INP", "r", stdin);
    std::freopen("output.OUT", "w", stdout);
}