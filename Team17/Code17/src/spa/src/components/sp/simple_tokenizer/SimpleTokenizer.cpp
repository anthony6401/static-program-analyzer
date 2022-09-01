#include "SimpleTokenizer.h"
#include <sstream>
#include <iostream>

SimpleTokenizer::SimpleTokenizer() {

}

void SimpleTokenizer::processCode(std::string code) {
    
}

std::vector<std::string> SimpleTokenizer::splitBracket(std::string code) {
    std::vector<std::string> tokens;
    std::stringstream stringstream(code);
    std::string line;
    while (std::getline(stringstream, line)) {
        std::size_t previous = 0;
        std::size_t current;
        while ((current = line.find_first_of("{};", previous)) != std::string::npos) {
            tokens.push_back(line.substr(previous, current - previous + 1));
            previous = current + 1;
        }
        if (previous < line.length()) {
            tokens.push_back(line.substr(previous, std::string::npos));
        }
    }
    return tokens;
}