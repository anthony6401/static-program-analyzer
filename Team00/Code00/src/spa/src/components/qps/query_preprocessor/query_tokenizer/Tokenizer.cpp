# include "Tokenizer.h"
#include <utility>
#include "TokenType.h"
#include "string"


using namespace qps;


Tokenizer::Tokenizer(std::string query) : query(query) {
    /**
     * Initialises unordered map of string values to tokens with initializer list.
     */
    stringToTokenMap = {
            {"Select", TokenType::SELECT},
            {"such", TokenType::SUCH},
            {"that", TokenType::THAT},
            {"Modifies", TokenType::MODIFIES},
            {"Uses", TokenType::USES},
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

