# include "Tokenizer.h"
#include <utility>
#include "TokenType.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <unordered_set>
#include "../exceptions/TokenException.h"

using namespace qps;

std::string whitespace = "\n\r\t\f\v";
std::unordered_set<char> expressionSymbols = {'+', '-', '*', '/', '%'};

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
            {"_", TokenType::WILDCARD},
            {",", TokenType::COMMA},
            {"(", TokenType::OPEN_BRACKET},
            {")", TokenType::CLOSED_BRACKET},
            {"\"", TokenType::QUOTATION_MARK},
            {";", TokenType::SEMI_COLON},
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

std::vector<std::string> formatCharToStringVector(std::string s, char delimiter) {
    std::vector<std::string> tokenValueString;
    std::stringstream ss(s);
    std::string tokenValue;

    while (getline(ss, tokenValue, delimiter)) {
        tokenValueString.push_back(tokenValue);
    }
    return tokenValueString;
}

bool charTypeToggler(bool isCharType) {
    return !isCharType;
}

std::vector<std::string> splitQuery(std::string query) {
    std::vector<char> char_output;
    char delimiter = '|';
    bool isWildcard = false;
    bool isIdentity = false;
    for (char c : query) {
        switch (c) {
            case '_':
                isWildcard = charTypeToggler(isWildcard);
                break;
            case '"':
                isIdentity = charTypeToggler(isIdentity);
                break;
            case ' ':
            case '\n':
            case '\t':
                if (!isWildcard && !isIdentity) {
                    char_output.push_back(delimiter);
                }
                break;
            case ';':
                char_output.push_back(delimiter);
                break;
            case ',':
                char_output.push_back(delimiter);
                if (isWildcard) {
                    isWildcard = charTypeToggler(isWildcard);
                }
                break;
            case '(':
                if (!isIdentity) {
                    char_output.push_back(delimiter);
                }
                break;
            case ')':
                if (!isIdentity) {
                    char_output.push_back(delimiter);
                }

                if (isWildcard) {
                    isWildcard = charTypeToggler(isWildcard);
                }
                break;
            default: break;
        }

        // Removes white spaces between identities and sub-expressions eg. "x + y" becomes "x+y"
        if (c != ' ') {
            char_output.push_back(c);
        }

        switch (c) {
            case ';':
            case ',':
                char_output.push_back(delimiter);
                break;
            case '(':
            case ')':
                if (!isIdentity) {
                    char_output.push_back(delimiter);
                }
                break;
            default: break;
        }
    }

    std::string string_output = std::string(char_output.begin(), char_output.end());
    std::vector<std::string> splittedQuery = formatCharToStringVector(string_output, delimiter);
    return splittedQuery;
}

/**
 * Trim the string to remove leading and trailing spaces
 */
std::string trimString(const std::string& s) {
    const auto beginning = s.find_first_not_of(whitespace);
    const auto ending = s.find_last_not_of(whitespace);
    const auto range = ending - beginning + 2;
    return s.substr(beginning, range);
}

// First attempt at string splitting, might require in the future

std::vector<std::string> split(std::string query) {
    std::vector<std::string> firstSplit = splitByDelimiter(query, ' ');
    char split_delimiter = '|';
    std::vector<char> char_output;
    for (const std::string s : firstSplit) {
        trimString(s);
        for (char c : s) {
            if (c == '"' || c == ',' || c == '(' || c == ')' || c == '\n' || c == '+' || c == '-') {
                char_output.push_back(split_delimiter);
                char_output.push_back(c);
            } else {
                char_output.push_back(c);
            }
        }
        char_output.push_back(split_delimiter);
    }

    std::string string_output = std::string(char_output.begin(), char_output.end());
    return formatCharToStringVector(string_output, split_delimiter);
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

std::string trimQuotesOrWildcard(std::string s) {
    return s.substr(1, s.size() - 2);
}

/**
 * Checks that string s follows the IDENTITY lexical syntax with Quotation Marks
 */
bool Tokenizer::isIdentity(std::string s) {
    std::cout << s << " in ident" << std::endl;
    if (s.size() <= 2) {
        return false;
    } else {
        if (s.front() == '"' && s.back() == '"') {
            if (isName(trimQuotesOrWildcard(s))) {
                return true;
            }
        }
    }
    return false;
}

// INCOMPLETE!!!
// "x+(x+2)" // "x+1"
bool Tokenizer::isExpression(std::string s) {
    std::cout << s << " in expr" << std::endl;
    if (s.size() < 5) { // Perhaps add in expression symbol checking
        return false;
    } else {
        if (s.front() == '"' && s.back() == '"') {
            std::string withoutQuotes = trimQuotesOrWildcard(s);
            for (char c : withoutQuotes) {
                if (isalnum(c)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// _"x+1"_, _"x"_, _"1"_
bool Tokenizer::isSubExpression(std::string s) {
    std::cout << s << " in subexpr" << std::endl;
    if (s.size() < 5) {
        return false;
    } else {
        if (s.front() == '_' && s.back() == '_') {
            std::string withoutWildcard = trimQuotesOrWildcard(s);
            bool isIdentity = Tokenizer::isIdentity(withoutWildcard);
           if (isIdentity || Tokenizer::isExpression(withoutWildcard) || Tokenizer::isInteger(trimQuotesOrWildcard(withoutWildcard))) {
               return true;
           }
        }
    }
    return false;
}

auto isEmptyOrBlank = [](const std::string &s) {
    return s.find_first_not_of(" \n\t") == std::string::npos;
};

/**
 * Tokenizes each character or string according to Token Types and outputs vector<TokenObject>
 */
std::vector<TokenObject> Tokenizer::tokenize(std::string query) {
    std::vector<TokenObject> tokenList;
    std::vector<std::string> tokenValues = splitQuery(query);

    // Remove empty strings from tokenized values
    tokenValues.erase(std::remove_if(tokenValues.begin(), tokenValues.end(), isEmptyOrBlank), tokenValues.end());

//    for (auto s : tokenValues) {
//        std::cout << s <<  std::endl;
//    }

    for (std::string s : tokenValues) {
        s = trimString(s);
        // Token value exists in list
        if (stringToTokenMap.find(s) != stringToTokenMap.end()) {
            TokenObject object = TokenObject(stringToTokenMap[s], s);
            tokenList.push_back(object);
        } else {
            if (isName(s)) {
                std::cout << s << " is name" << std::endl;
                TokenObject object = TokenObject(TokenType::NAME, s);
                tokenList.push_back(object);
            } else if (isInteger(s)) {
                std::cout << s << " is int" << std::endl;
                TokenObject object = TokenObject(TokenType::INTEGER, s);
                tokenList.push_back(object);
            } else if (isIdentity(s)) {
                std::cout << s << " is ident" << std::endl;
                std::string trimmedQuotesFromIdentity = trimQuotesOrWildcard(s);
                TokenObject object = TokenObject(TokenType::NAME_WITH_QUOTATION, trimmedQuotesFromIdentity);
                tokenList.push_back(object);
            } else if (isExpression(s)) {
                std::cout << s << " is expr" << std::endl;
                // Return trimmed string
                std::string trimmedQuotesFromExpression = trimQuotesOrWildcard(s);
                TokenObject object = TokenObject(TokenType::EXPRESSION, trimmedQuotesFromExpression);
                tokenList.push_back(object);
            } else if (isSubExpression(s)) {
                std::cout << s << " is subexpression" << std::endl;
                std::string trimmedQuotesFromSubExpression = trimQuotesOrWildcard(s);
                std::string trimmedWildcardAndQuotesFromSubExpression = trimQuotesOrWildcard(trimmedQuotesFromSubExpression);
                TokenObject object = TokenObject(TokenType::SUBEXPRESSION, trimmedWildcardAndQuotesFromSubExpression);
                tokenList.push_back(object);
            } else {
                // throw exception
                throw TokenException();
            }
        }
    }
    return tokenList;
}





