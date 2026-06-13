#include "../../../helpers/helpers.hpp"
#include <algorithm>

struct Transmission {
    std::string code;
    char character;
}; // Defines a transmission

int main() {
    setup();

    std::vector<Transmission> transmissions = {}; // Initializes the list of transmissions
    while (true) {
        std::string line;
        std::getline(std::cin, line); // Get each line

        if (line == "") {
            break;
        }

        std::vector<std::string> parts = string::split(line, ','); // Splits the line into 2 parts by a comma
        transmissions.push_back({parts[0], parts[1][0]});
    }

    std::sort(transmissions.begin(), transmissions.end(), [](Transmission a, Transmission b){
        return a.character < b.character;
    }); // Sorts by the character

    
    return 0;
}