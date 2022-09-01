#include "SimpleTokenizer.h"
#include "../utils/SpUtils.h"

SimpleTokenizer::SimpleTokenizer(std::string code) {
    std::regex lineDelimiters = std::regex("[^{};]*[{};]");
    std::regex tokenDelimiters = std::regex("(==)|(!=)|(&&)|(\|\|)|(>=)|(<=)|[!%+\-/*=(){};<>]");
    std::regex whiteSpace = std::regex("\s+");
    std::vector<std::string> codeLines = SpUtils::split(code, lineDelimiters);

    if (codeLines.empty()) {
        throw std::invalid_argument("Received invalid SIMPLE code");
    }

    for (std::string line : codeLines) {
        line = std::regex_replace(line, tokenDelimiters, " $& ");
        std::vector<std::string> lineTokens = SpUtils::split(code, whiteSpace);
    }

}
