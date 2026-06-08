#include "../../../helpers/helpers.hpp"
#include <unordered_map>

int main() {
    setup();

    // List out all of the possible morse codes as shown in the problem
    std::unordered_map<std::string, char> morse_map = {
        {"._", 'A'},
        {"_...", 'B'},
        {"_._.", 'C'},
        {"_..", 'D'},
        {".", 'E'},
        {".._.", 'F'},
        {"__.", 'G'},
        {"....", 'H'},
        {"..", 'I'},
        {".___", 'J'},
        {"_._", 'K'},
        {"._..", 'L'},
        {"__", 'M'},
        {"_.", 'N'},
        {"___", 'O'},
        {".__.", 'P'},
        {"__._", 'Q'},
        {"._.", 'R'},
        {"...", 'S'},
        {"_", 'T'},
        {".._", 'U'},
        {"..._", 'V'},
        {".__", 'W'},
        {"_.._", 'X'},
        {"_.__", 'Y'},
        {"__..", 'Z'},
        {"._._._", '.'},
        {"..__..", '?'},
        {"_._.__", '!'},
        {"_...._", '-'}
    };

    std::string sentence = ""; // Initializes the variable
    while (true) {
        std::string line;
        std::getline(std::cin, line); // Get each line

        if (line == "") {
            // If there is no more input, then break out
            break;
        }

        std::string word = ""; // Initializes the word
        std::vector<std::string> tokens = string::split(line); // Splits the line into "characters" which is represented by morse
        for (const std::string &token : tokens) {
            word += morse_map[token]; // Adds each character to the word
        }

        sentence += word + " "; // Adds the word into the variable
    }

    std::cout << sentence; // Our result is here
    return 0;
}