#include "SpUtils.h"

std::vector<std::string> SpUtils::split(std::string code, std::string delimiters) {
    std::vector<std::string> tokens;
    std::regex rgx(delimiters);
    std::regex_iterator<std::string::iterator> start(code.begin(), code.end(), rgx);
    std::regex_iterator<std::string::iterator> end;

    while (start != end) {
        std::string token = start->str();
        tokens.push_back(token);
        ++start;
    }
    return tokens;
}