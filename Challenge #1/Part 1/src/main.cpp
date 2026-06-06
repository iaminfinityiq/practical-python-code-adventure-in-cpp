#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdio>

void setup() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::freopen("input.INP", "r", stdin);
    std::freopen("output.OUT", "w", stdout);
}

int main() {
    setup();

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

    std::string sentence = "";
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        if (line == "") {
            break;
        }

        std::string word = "";
        std::string current_token = "";
        for (char &c : line + " ") {
            if (c == ' ' && current_token != "") {
                word += morse_map[current_token];
                current_token = "";
            } else {
                current_token += c;
            }
        }

        sentence += word + " ";
    }

    std::cout << sentence;
    return 0;
}