#include "SimpleValidator.h"

/// <summary>Validates lexically token</summary>
/// <param name="token">Pointer to token to validate lexically</param>
/// <returns>True if valid lexically and false if not</returns>
bool SimpleValidator::validateLexical(std::string& token) {
    return std::find_if(token.begin(), token.end(), 
        [](char c) { return !(std::isalnum(c)); }) == token.end();
}
