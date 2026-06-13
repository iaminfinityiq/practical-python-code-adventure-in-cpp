#include "../../../helpers/helpers.hpp"

// A struct used for tracking how many characters are there in a row
struct CharactersStruct {
    bool is_one; // Uses a boolean instead of a char to save space. '1' is true and '2' is false
    size_t characters; // How many consecutive characters are there
};

// Function used to step the iteration by 1 step
void iterate(std::string &input) {
    std::vector<CharactersStruct> characters = {}; // Initializes the characters vector
    bool current_character = (input[0] == '1'); // Stores the character that we starts with. Here the input is guaranteed to not be empty
    size_t consecutive_characters = 0; // Tracks how many consecutive characters are there. Here we initializes to 0 so in the iteration it adds to 1
    
    // Iterate each character
    for (char c : input) {
        if ((c == '1') != current_character) { // If the character is not same as the character we needed
            characters.push_back({current_character, consecutive_characters}); // Pushes the character chunk data
            current_character = !current_character; // Inverts the character
            consecutive_characters = 1; // Sets back the character count to 1
        } else { // The streak keeps going
            consecutive_characters++;
        }
    }

    characters.push_back({current_character, consecutive_characters}); // Pushes back the last character
    input = ""; // Resets the input

    // Iterates each element in the characters vector
    for (CharactersStruct &character : characters) {
        // Step 1: Squeezes all of the 2 inputs
        for (size_t i = character.characters; i >= 2; i -= 2) {
            input += "2"; // Pushes 2
            if (character.is_one) {
                // Two 1s
                input += "1"; // Pushes 1
            } else {
                // Two 2s
                input += "2";
            }
        }

        // Step 2: If there is a remainder 1, push it
        if (character.characters & 1) { // character.characters & 1 is an AND bitwise operation which gets the remainder when divided by 2
            input += "1"; // Pushes 1
            if (character.is_one) {
                // One 1
                input += "1"; // Pushes 1
            } else {
                // One 2
                input += "2";
            }
        }
    }
}

int main() {
    setup();

    // Get the input
    std::string input;
    std::cin >> input;

    // Run 65 iterations
    for (size_t i = 0; i < 65; i++) {
        iterate(input); // Iterate the input
    }

    std::cout << input.size(); // Our result is here
    return 0;
}