#include "../../../helpers/helpers.hpp"
#include <unordered_map>
#include <algorithm>
#include <map>

int main() {
    setup();
    
    // Get the original alphabet
    std::string original_letters;
    std::getline(std::cin, original_letters);

    // Get the reversed alphabet
    std::string reversed_tmp;
    std::getline(std::cin, reversed_tmp);

    std::u32string reversed_letters = utf8::utf8_to_u32(reversed_tmp); // Convert the reversed alphabet into u32

    // Maps the original alphabet to the reversed alphabet
    std::unordered_map<unicode_char, char> mappings = {}; // Initializes the mappings
    for (size_t i = 0; i < original_letters.size(); i++) { // Iterates through the alphabet
        mappings[reversed_letters[i]] = original_letters[i]; // Maps the reversed character to the original character
    }

    // Skips the empty line
    std::string line;
    std::getline(std::cin, line);

    bool reversed = false; // Instead of using integers to represent oddity, we use booleans
    std::string full_message = "";
    while (true) {
        line = ""; // Clears out the line
        std::getline(std::cin, line); // Gets the input from the line
        if (line == "") {
            // Break out the loop if there's no more input
            break;
        }

        if (reversed) {
            // If the line is reversed
            std::u32string reversed_line = utf8::utf8_to_u32(line); // Turn the string to u32 string
            std::string translated_line = ""; // Initialize the translated line
            for (unicode_char &c : reversed_line) { // Loops through the reversed line
                if (c == ' ') {
                    translated_line = " " + translated_line; // Exception for the space characters since they are not in the mappings
                    continue;
                }

                if (mappings.count(c)) { // Filters out all of the punctuation at the same time
                    translated_line = std::string("") + mappings[c] + translated_line; // Adds each character corresponding to the mappings
                }
            }
            
            full_message += translated_line; // Adds the full line to the message
        } else {
            // If the line is not reversed
            std::string translated_line = ""; // Initializes the translated line
            for (char &c : line) { // Iterates through each character
                if (c == ' ' || ('A' <= c && c <= 'Z')) { // Filters out all of the punctuation at the same time
                    translated_line += c;
                }
            }

            full_message += translated_line; // Adds the full line to the message
        }

        reversed = !reversed; // Toggle the boolean
    }

    std::map<std::string, bool> verified_words = {}; // Initializes a set of verified words
    std::vector<std::string> words = string::split(full_message); // Splits the message into the words;
    for (std::string &word : words) {
        if (word.size() == 5) {
            verified_words[word] = true; // Pushes the word if it has exactly 5 characters
        }
    }

    size_t i = 1; // Represents the ith word
    for (auto &it : verified_words) {
        if (i == 20) {
            // If we reached the 20th word, then print out the result
            std::cout << it.first; // Our result is here
            return 0;
        }

        i++; // Increments i
    }

    return 0;
}