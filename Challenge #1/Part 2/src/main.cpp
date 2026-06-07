#include "../../../helpers/helpers.hpp"
#include <unordered_map>

int main() {
    setup();

    // Gets the input
    std::string input;
    std::cin >> input;

    // Turns the decyphered input into binary
    std::u32string decoded = utf8::utf8_to_u32(input); // Turns the input into std::u32string
    std::string decoded_input = ""; // Initializes the variable
    for (unicode_char &c : decoded) {
        decoded_input += std::to_string(static_cast<int32_t>(c)); // Decodes their ordinal values
    }

    std::string binary = string::number_representation_to_binary(decoded_input, '_', '.'); // Turns the decoded input to binary

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

    std::string morse = string::replace(binary, "_._.__", " "); // Removes !
    std::vector<std::string> characters = string::split(morse); // Turns to morse characters

    std::string word = ""; // Initializes the word variable
    for (std::string &morse_char : characters) {
        word += morse_map[morse_char]; // Adds the corresponding morse character to the result
    }

    std::cout << word; // Our result is here
    return 0;
}