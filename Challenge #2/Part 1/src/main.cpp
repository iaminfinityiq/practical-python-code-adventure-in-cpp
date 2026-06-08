#include "../../../helpers/helpers.hpp"
#include <algorithm>

struct Line {
    std::string title;
    size_t chapter;
    char subchapter;
    size_t section;
}; // Defines a line with a title, chapter, subchapter and section

int main() {
    setup();

    std::string line;
    std::getline(std::cin, line); // Skips the first line

    std::vector<Line> lines = {}; // Initializes the vector of lines
    while (true) {
        line = ""; // Clears out the line before taking in input
        std::getline(std::cin, line); // Gets the line input
        if (line == "") {
            // Breaks out the loop if there is no more input
            break;
        }

        std::vector<std::string> attributes = string::split(line, ','); // Splits the attributes by comma
        lines.push_back({attributes[0], std::stoull(attributes[1]), attributes[2][0], std::stoull(attributes[3])}); // Makes the line struct and pushes to the lines vector
    }

    std::sort(lines.begin(), lines.end(), [](Line a, Line b){
        if (a.chapter != b.chapter) { // Sorts by chapter first
            return a.chapter < b.chapter;
        }

        if (a.subchapter != b.subchapter) { // Then subchapter
            return a.subchapter < b.subchapter;
        }

        return a.section < b.section; // And finally the section
    }); // Sorts out the vector with the condition given in the question

    std::string message = ""; // Initializes the message
    for (Line &line : lines) {
        message += line.title[0]; // Adds the first letter of each title
    }

    std::cout << message; // Our result is here
    return 0;
}