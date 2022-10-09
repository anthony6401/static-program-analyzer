#include "SimpleTokenizer.h"
#include "../utils/SpUtils.h"

std::vector<std::string> SimpleTokenizer::tokenizeCode(std::string code) {
    std::regex lineDelimiters = std::regex("[^{};]*[{};]");
    return SpUtils::split(code, lineDelimiters);
}

std::vector<std::string> SimpleTokenizer::tokenizeLine(std::string code) {
    std::regex tokenDelimiters = std::regex("(==)|(!=)|(&&)|(\\|\\|)|(>=)|(<=)|[!%+\\-/*=(){};<>]");
    std::regex notWhiteSpace = std::regex("\\S+");
    std::string line = std::regex_replace(code, tokenDelimiters, " $& ");
    return SpUtils::split(line, notWhiteSpace);
}
