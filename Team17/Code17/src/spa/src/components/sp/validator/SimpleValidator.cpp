#include "SimpleValidator.h"

bool SimpleValidator::validateLexical(std::string& token) {
    return std::find_if(token.begin(), token.end(), 
        [](char c) { return !(std::isalnum(c)); }) == token.end();
}
