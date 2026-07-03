#include "../../../helpers/helpers.hpp"

int main() {
    setup();

    // Initializes the width and height
    size_t width = 0;
    size_t height = 0;

    while (true) {
        std::string line;
        std::getline(std::cin, line); // Gets the input of the line
        if (line == "") {
            // Breaks out of the loop if there is no more input
            break;
        }

        // Get the width size if width is 0, aka haven't received the input yet
        if (width == 0) {
            width = line.size();
        }

        height++; // Increments the height
    }

    fraction::Fraction slope = fraction::divide(fraction::whole_to_fraction(height), fraction::whole_to_fraction(width)); // Gets the slope
    fraction::Fraction y = fraction::ZERO; // Initializes the y coordinate
    size_t cells = 0; // Initializes the cell count
    for (size_t x = 0; x < width; x++) { // The loop runs for each iteration for x
        size_t old_ceil = y.ceil(); // Get the old ceiling
        bool not_integer = !y.is_integer(); // Checks if the fraction is an integer
        y = fraction::add(y, slope); // Adds slope to y
        size_t new_ceil = y.ceil(); // Gets the new ceiling
        cells += new_ceil - old_ceil + not_integer; // Adds the corresponding amount of cells
    }

    std::cout << cells; // Our result is here
    return 0;
}