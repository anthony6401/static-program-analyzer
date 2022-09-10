#include "SimpleTokenizer.h"
#include "../parser/SimpleParser.h"
#include "../utils/SpUtils.h"

SimpleTokenizer::SimpleTokenizer(Extractor* extractor) {
    this->extractor = extractor;
}

/// <summary>
/// Main method to tokenize SIMPLE code for design extractor
/// </summary>
/// <param name="code">SIMPLE code to be processed</param>
void SimpleTokenizer::tokenizeCode(std::string code) {
    std::regex lineDelimiters = std::regex("[^{};]*[{};]");
    std::regex tokenDelimiters = std::regex("(==)|(!=)|(&&)|(\\|\\|)|(>=)|(<=)|[!%+\\-/*=(){};<>]");
    std::regex whiteSpace = std::regex("\\S+");

    std::vector<std::string> codeLines = SpUtils::split(code, lineDelimiters);
    if (codeLines.empty()) {
        throw std::invalid_argument("Received invalid SIMPLE code");
    }

    for (std::string line : codeLines) {
        line = std::regex_replace(line, tokenDelimiters, " $& ");
        std::vector<std::string> lineTokens = SpUtils::split(line, whiteSpace);
        SimpleToken lineToken = SimpleParser::parseLine(lineTokens, line);
        (lineToken.parseFunction)(lineToken, lineTokens, extractor);
    }
}
