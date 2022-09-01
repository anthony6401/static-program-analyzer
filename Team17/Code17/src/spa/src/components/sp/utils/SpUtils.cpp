#include "SpUtils.h"

std::vector<std::string> SpUtils::split(std::string code, std::regex delimiters) {
    std::vector<std::string> tokens;
    std::regex_iterator<std::string::iterator> start(code.begin(), code.end(), delimiters);
    std::regex_iterator<std::string::iterator> end;

    while (start != end) {
        std::string token = start->str();
        tokens.push_back(token);
        ++start;
    }
    return tokens;
}