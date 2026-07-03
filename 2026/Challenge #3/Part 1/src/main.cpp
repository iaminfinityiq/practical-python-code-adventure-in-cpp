#include "../../../helpers/helpers.hpp"
#include <algorithm>
#include <iterator>

int main() {
    setup();

    std::vector<size_t> spearheads = {}; // Saves the size of the spearheads
    while (true) {
        std::string line;
        std::getline(std::cin, line); // Gets the input of the line
        if (line == "") {
            // Breaks out of the loop if there's no more input
            break;
        }

        // Removes spaces and dashes
        std::string new_line = string::replace(line, '-', "");
        new_line = string::replace(new_line, ' ', "");
        if (new_line == "") {
            continue; // If the line is empty, then skip it
        }

        size_t spearhead_size = std::stoull(new_line); // Converts the line into an unsigned integer
        spearheads.push_back(spearhead_size); // Pushes the new integer
    }

    // Stores the largest element in the array at each iteration
    std::vector<size_t> largest = spearheads;
    std::sort(largest.begin(), largest.end(), [](size_t a, size_t b){
        return a > b;
    });

    size_t flips = 0;
    for (size_t &spearhead : largest) { // Iterate until spearheads are sorted, in this case it does not have to be sorted because we only need to count how many flips are there, instead we can pop the array
        if (*spearheads.rbegin() == spearhead) {
            spearheads.pop_back(); // No flips are needed, the spearhead is already at the back of the stack
            continue; // Skips the other processes
        }

        auto position = std::find(spearheads.begin(), spearheads.end(), spearhead); // Find the position of the corresponding spearhead
        if (position != spearheads.begin()) {
            // Do a partial flip, counts as 1 flip
            std::reverse(spearheads.begin(), std::next(position));
            flips++;
        }

        // Flips the whole array, counts as 1 flip
        std::reverse(spearheads.begin(), spearheads.end());
        flips++;

        spearheads.pop_back(); // Pops the last element of the stack
    }

    std::cout << flips; // Our result is here
    return 0;
}