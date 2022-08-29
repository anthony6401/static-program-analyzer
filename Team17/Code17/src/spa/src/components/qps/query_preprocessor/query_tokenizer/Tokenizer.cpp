# include "Tokenizer.h"
#include <utility>
#include "TokenType.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


using namespace qps;

std::string whitespace = " \\t";

Tokenizer::Tokenizer() {
    /**
     * Initialises unordered map of string values to tokens with initializer list.
     */
    stringToTokenMap = {
            {"Select", TokenType::SELECT},
            {"such", TokenType::SUCH},
            {"that", TokenType::THAT},
            {"Modifies", TokenType::MODIFIES},
            {"Uses", TokenType::USES},
            {"Parent", TokenType::PARENT},
            {"Parent*", TokenType::PARENT_T},
            {"Follows", TokenType::FOLLOWS},
            {"Follows*", TokenType::FOLLOWS_T},
            {"pattern", TokenType::PATTERN},
            {"_", TokenType::UNDERSCORE},
            {",", TokenType::COMMA},
            {"(", TokenType::OPEN_BRACKET},
            {")", TokenType::CLOSED_BRACKET},
            {"\"", TokenType::QUOTATION_MARK},
            {";", TokenType::SEMI_COLON},
            {"+", TokenType::PLUS},
            {"-", TokenType::MINUS},
            {"/", TokenType::DIVIDE},
            {"*", TokenType::MULTIPLY},
            {"%", TokenType::PERCENTAGE},
            {"stmt", TokenType::STMT},
            {"read", TokenType::READ},
            {"print", TokenType::PRINT},
            {"call", TokenType::CALL},
            {"while", TokenType::WHILE},
            {"if", TokenType::IF},
            {"assign", TokenType::ASSIGN},
            {"variable", TokenType::VARIABLE},
            {"constant", TokenType::CONSTANT},
            {"procedure", TokenType::PROCEDURE}
    };
}


template <typename Out>
void splitIterator(const std::string query, char delim, Out result) {
    std::istringstream iss(query);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> splitByDelimiter(const std::string query, char delim) {
    std::vector<std::string> elems;
    splitIterator(query, delim, std::back_inserter(elems));
    return elems;
}

/**
 * Tokenizes each character or string according to Token Types and outputs vector<TokenObject>
 */
std::vector<std::string> Tokenizer::tokenize(std::string query) {
    return splitByDelimiter(query, ' ');
}

std::vector<std::string> splitQuery(std::string &query) {

    for (char c : query) {

    }
}


/**
 * Trim the string to remove leading and trailing spaces
 */
std::string Tokenizer::trimString(const std::string& s) {
    const auto beginning = s.find_first_not_of(whitespace);
    const auto ending = s.find_last_not_of(whitespace);
    const auto range = ending - beginning + 2;
    return s.substr(beginning, range);
}

/**
 * Checks that string s follows the NAME lexical syntax
 */
bool Tokenizer::isName(std::string s) {
    if (!isalpha(s[0]) || s.empty()) {
        return false;
    }
    for (const auto c : s) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

/**
 * Checks that string s follows the INTEGER lexical syntax
 */
bool Tokenizer::isInteger(std::string s) {
    if (s[0] == '0' && s.length() > 1) {
        return false;
    }
    for (const auto c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

