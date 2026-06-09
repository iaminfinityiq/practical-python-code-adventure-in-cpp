#include "../../../helpers/helpers.hpp"
#include <unordered_map>

int main() {
    setup();

    // Gets input from 4 lines, each variable name has a direction which corresponds to where the letter is pointing at
    std::u32string north_alphabet = utf8::input_getline();
    std::u32string east_alphabet = utf8::input_getline();
    std::u32string west_alphabet = utf8::input_getline();
    std::u32string south_alphabet = utf8::input_getline();

    // Initializes the mappings for all 4 directions
    std::unordered_map<unicode_char, char> north_mappings = {};
    std::unordered_map<unicode_char, char> east_mappings = {};
    std::unordered_map<unicode_char, char> west_mappings = {};
    std::unordered_map<unicode_char, char> south_mappings = {};

    size_t i = 0; // Shows which index to point for each character
    for (char c = 'A'; c <= 'Z'; c++) { // Loops through the normal alphabet
        // Assigns each character from each alphabet to the corresponding character
        north_mappings[north_alphabet[i]] = c;
        east_mappings[east_alphabet[i]] = c;
        west_mappings[west_alphabet[i]] = c;
        south_mappings[south_alphabet[i]] = c;
        
        i++; // Increments the index to point
    }

    std::string line; // Initializes the line variable
    std::getline(std::cin, line); // Skips through the empty line

    std::vector<std::u32string> data = {}; // Represents the data
    while (true) {
        line = ""; // Resets the line
        std::getline(std::cin, line); // Gets input from the line
        if (line == "") {
            // Breaks out of the loop if there is no input
            break;
        }

        data.push_back(utf8::utf8_to_u32(line)); // Pushes the std::u32string line to the data
    }

    size_t x = 0; // Represents the current x position on the matrix
    size_t y = 0; // Represents the current y position on the matrix
    size_t dx = 1; // Represents how much change in x per tick
    size_t dy = 0; // Represents how much change in y per tick
    std::string message = ""; // Represents the message
    std::unordered_map<size_t, std::unordered_map<size_t, bool>> visited = {}; // A matrix that represents if you have visited that position
    while (0 <= y && y < data.size() && 0 <= x && x < data[y].size() && !visited[x][y]) { // The condition for the loop to run is that y has to be in the bounds, x has to be in the bounds, and at coordinate (x, y) hasn't been visited
        visited[x][y] = true;
        unicode_char character = data[y][x];
        if (north_mappings.count(character)) {
            // The character is pointing north, so dx = 1 and dy = 0
            dx = 1;
            dy = 0;
            message += north_mappings[character];
        } else if (east_mappings.count(character)) {
            // The character is pointing east, so dx = 0 and dy = 1
            dx = 0;
            dy = 1;
            message += east_mappings[character];
        } else if (west_mappings.count(character)) {
            // The character is pointing west, so dx = 0 and dy = -1
            dx = 0;
            dy = -1;
            message += west_mappings[character];
        } else if (south_mappings.count(character)) {
            // The character is pointing south, so dx = -1 and dy = 0
            dx = -1;
            dy = 0;
            message += south_mappings[character];
        } else {
            // These are punctuations, so we leave them as they are
            message += character;
        }

        // Change the position based on dx and dy
        x += dx;
        y += dy;
    }

    std::cout << message; // Our result is here
    return 0;
}