#include "../../../helpers/helpers.hpp"
#include <algorithm>
#include <iterator>

// A struct representing a spearhead
struct Spearhead {
    size_t size; // What size is it?
    bool is_up; // Is it facing convex side up?
};

// A function helps swapping from the top of the staack to the desired position
void flip(std::vector<Spearhead> &spearheads, std::vector<Spearhead>::iterator position) {
    for (auto it = spearheads.begin(); it != position; it++) { // Iterate through each position
        it->is_up = !it->is_up; // Flip the side
    }

    std::reverse(spearheads.begin(), position);
}

int main() {
    setup();

    std::vector<Spearhead> spearheads = {}; // Saves all of the spearheads
    while (true) {
        std::string line;
        std::getline(std::cin, line); // Gets the input of the line
        if (line == "") {
            // Breaks out of the loop if there's no more input
            break;
        }

        std::string new_line = string::replace(line, ' ', ""); // Removes spaces
        if (new_line == "") {
            continue; // Skips if the line is empty at the moment
        }

        bool is_up = new_line[0] != '-'; // Checks if the spearhead is convex side up
        new_line = string::replace(new_line, '-', ""); // Removes dashes
        if (new_line == "") {
            continue; // Skips if the line only contains dashes
        }

        size_t spearhead_size = std::stoull(new_line); // Now we know what the spearhead size is
        spearheads.push_back({spearhead_size, is_up}); // Pushes the corresponding spearhead
    }

    // Stores the largest element in the array at each iteration
    std::vector<Spearhead> largest = spearheads;
    std::sort(largest.begin(), largest.end(), [](Spearhead a, Spearhead b){
        return a.size > b.size;
    });

    size_t flips = 0;
    for (Spearhead &spearhead : largest) { // Iterate until spearheads are sorted, in this case it does not have to be sorted because we only need to count how many flips are there, instead we can pop the array
        if (spearheads.rbegin()->size == spearhead.size) {
            if (spearheads.rbegin()->is_up) { // If the spearhead is in the correct orientation, leave them be
                spearheads.pop_back(); // No flips are needed
                continue;
            }

            // Flips the whole stack of spearheads instead
            flip(spearheads, spearheads.end());
            flips++;
        } else if (spearheads.begin()->size != spearhead.size) {
            auto final_dest = spearheads.end(); // Stores the iterator containing the corresponding spearhead size, default to the end iterator
            for (auto it = spearheads.begin(); it != spearheads.end(); it++) { // Loops through each iterator
                if (it->size == spearhead.size) {
                    // We got our final destination. It is guaranteed that we can find a position
                    final_dest = it;
                    break;
                }
            }

            // Flips until the desired position
            flip(spearheads, std::next(final_dest));
            flips++;
        }

        // Now the spearhead is at the top
        if (spearheads[0].is_up) { // If the spearhead is at the correct orientation, we want it to be the incorrect orientation instead
            // Flips the top spearhead
            spearheads[0].is_up = false;
            flips++;
        }

        // And finally flip the whole stack
        flip(spearheads, spearheads.end());
        flips++;

        spearheads.pop_back(); // Pops the last element of the stack
    }

    std::cout << flips; // Our result is here
    return 0;
}