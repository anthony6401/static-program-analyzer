# include "Tokenizer.h"
#include <utility>
#include "TokenType.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <stack>
#include <iostream>
#include <unordered_set>
#include "../exceptions/TokenException.h"

using namespace qps;

std::string whitespace = "\n\r\t\f\v";
std::unordered_set<char> expressionSymbolsAndBrackets = {'(', ')', '+', '-', '*', '/', '%'};
std::unordered_set<std::string> expressionSymbols = {"+", "-", "*", "/", "%"};

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
            {"Next", TokenType::NEXT},
            {"Next*", TokenType::NEXT_T},
            {"Calls", TokenType::CALLS},
            {"Calls*", TokenType::CALLS_T},
            {"Affects", TokenType::AFFECTS},
            {"Affects*", TokenType::AFFECTS_T},
            {"with", TokenType::WITH},
            {"and", TokenType::AND},
            {"BOOLEAN", TokenType::BOOLEAN},
            {"_", TokenType::WILDCARD},
            {",", TokenType::COMMA},
            {"(", TokenType::OPEN_BRACKET},
            {")", TokenType::CLOSED_BRACKET},
            {"\"", TokenType::QUOTATION_MARK},
            {";", TokenType::SEMI_COLON},
            {"=", TokenType::EQUALS},
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

bool isEmptySpace(char character) {
    std::vector<char> emptyCharVector = {' ', '\n', '\t', '\v', '\f', '\r'};
    bool isEmpty = std::count(emptyCharVector.begin(), emptyCharVector.end(), character);
    return isEmpty;
}

void removeDelimiter(std::vector<char> &char_output, char delimiter) {
    int currLength = char_output.size() - 1;
    for (int i = currLength; i >= 0; i--) {
        if (char_output[i] == delimiter || isEmptySpace(char_output[i])) {
            char_output.erase(char_output.begin() + i);
        } else {
            break;
        }
    }
}

std::vector<std::string> splitQuery(std::string query) {
    std::vector<char> char_output;
    char delimiter = '|';
    bool isWildcard = false;
    bool isQuotes = false;
    bool isTuple = false;
    bool isAttribute = false;
    for (char c : query) {
        switch (c) {
            case '_':
                isWildcard = charTypeToggler(isWildcard);
                break;
            case '"':
                isQuotes = charTypeToggler(isQuotes);
                break;
            case '<':
                isTuple = charTypeToggler(isTuple);
                char_output.push_back(delimiter);
                break;
            case '>':
                isTuple = charTypeToggler(isTuple);
                break;
            case ' ':
            case '\n':
            case '\t':
            case '\v':
            case '\f':
            case '\r':
                if (!isWildcard && !isQuotes && !isTuple && !isAttribute) {
                    char_output.push_back(delimiter);
                }
                break;
            case '=':
                if (!isTuple) {
                    char_output.push_back(delimiter);
                }
                break;
            case ';':
                if (!isTuple) {
                    char_output.push_back(delimiter);
                }
                break;
            case ',':
                if (!isTuple) {
                    char_output.push_back(delimiter);
                }
                if (isWildcard) {
                    isWildcard = charTypeToggler(isWildcard);
                }
                break;
            case '(':
                if (!isQuotes) {
                    char_output.push_back(delimiter);
                }
                break;
            case ')':
                if (!isQuotes) {
                    char_output.push_back(delimiter);
                }

                if (isWildcard) {
                    isWildcard = charTypeToggler(isWildcard);
                }
                break;
            case '.':
                isAttribute = charTypeToggler(isAttribute);
                removeDelimiter(char_output, delimiter);
                break;
            default: break;
        }

        if (c != ' ') {
            char_output.push_back(c);
            if (isAttribute && c != '.') {
                isAttribute = charTypeToggler(isAttribute);
            }
        }

        switch (c) {
            case ';':
            case ',':
            case '=':
                if (!isTuple) {
                    char_output.push_back(delimiter);
                }
                break;
            case '(':
            case ')':
                if (!isQuotes) {
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
    if (s.size() <= 2) {
        return false;
    } else {
        s = trimString(s);
        if (s.front() == '"' && s.back() == '"') {
            if (isName(trimQuotesOrWildcard(s))) {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::string> Tokenizer::convertExpressionToStringVector(std::string s) {
    std::vector<std::string> expressionTokens;
    std::vector<std::string> invalidExpression;
    std::string temp;
    for (char character : s) {
        auto symbolsIterator = std::find(expressionSymbolsAndBrackets.begin(), expressionSymbolsAndBrackets.end(), character);
        if (symbolsIterator != expressionSymbolsAndBrackets.cend()) {
            if (!temp.empty()) {
                if (isName(temp) || Tokenizer::isInteger(temp)) {
                    expressionTokens.push_back(temp);
                    temp.clear();
                } else {
                    return invalidExpression;
                }
            }
            expressionTokens.push_back(std::string(1, character));
        } else {
            temp.push_back(character);
        }
    }

    if (!temp.empty()) {
        if (!isName(temp) && !isInteger(temp)) {
            return invalidExpression;
        } else {
            expressionTokens.push_back(temp);
        }
    }

    return expressionTokens;
}

bool Tokenizer::validateExpression(std::vector<std::string> expressionVector) {
    std::stack<std::string> expressionStack;
    std::string prev = "";
    bool isPrevName = false;
    bool isPrevInteger = false;
    for (auto string : expressionVector) {
        if (string == "(") {
            if (isPrevInteger || isPrevName) {
                return false;
            }
            expressionStack.push(string);
            prev = "(";
            isPrevInteger = false;
            isPrevName = false;
        } else if (string == ")") {
            if (expressionStack.empty() || expressionStack.top() != "(" || expressionSymbols.count(prev) || prev == "(") {
                return false;
            } else {
                expressionStack.pop();
                prev = ")";
            }
            isPrevInteger = false;
            isPrevName = false;
        } else {
            // Name, Integer or Mathematical symbols
            if (isName(string)) {
                if (isPrevName) {
                    return false;
                } else {
                    isPrevName = true;
                    prev = string;
                }
            } else if (isInteger(string)) {
                if (isPrevInteger) {
                    return false;
                } else {
                    isPrevInteger = true;
                    prev = string;
                }
            } else if (expressionSymbols.count(string)) {
                if (expressionSymbols.count(prev) || prev == "(" || prev.empty()) {
                    return false;
                }
                prev = string;
                isPrevInteger = false;
                isPrevName = false;
            }
        }
    }

    if (expressionSymbols.count(prev)) {
        return false;
    }

    if (!expressionStack.empty()) {
        return false;
    }
    return true;
}

 //"x+(x+2)" // "x+1" // "1"
bool Tokenizer::isExpression(std::string s) {
     if (s.size() < 3) {
         return false;
     }
     if (s.front() != '"' || s.back() != '"') {
         return false;
     }

     if (s.front() == '"' && s.back() == '"') {
         // Removes quotations
         std::string trimmedQuotes = trimQuotesOrWildcard(s);
         // Break string into char and validate char
         std::vector<std::string> expressionVector = convertExpressionToStringVector(trimmedQuotes);
         // Invalid expression
         if (expressionVector.empty()) {
             return false;
         } else {
             // Validate expression
             bool isValidExpresion = validateExpression(expressionVector);
             return isValidExpresion;
         }
     }
     return false;
}

// _"x+1"_, _"x"_, _"1"_
bool Tokenizer::isSubExpression(std::string s) {
    if (s.size() < 5) {
        return false;
    } else {
        if (s.front() == '_' && s.back() == '_') {
            std::string withoutWildcard = trimQuotesOrWildcard(s);
            bool isIdentity = Tokenizer::isIdentity(withoutWildcard);
            bool isExpression = Tokenizer::isExpression(withoutWildcard);
           if (isIdentity || isExpression) {
               return true;
           }
        }
    }
    return false;
}

auto isEmptyOrBlank = [](const std::string &s) {
    return s.find_first_not_of(" \n\t\f\v\r") == std::string::npos;
};

bool Tokenizer::isTuple(std::string s) {
    if (s.front() == '<' && s.back() == '>') {
        std::string currString = s.substr(1, s.length() - 2);
        std::string currValue;
        while (currString.length() > 0) {
            size_t commaIndex = currString.find(',');
            if (commaIndex != std::string::npos && commaIndex > 0) {
                currValue = currString.substr(0, commaIndex);

                if (!isName(currValue) && !isValidAttribute(currValue)) {
                    return false;
                }

                currString = currString.substr(commaIndex + 1, currString.length() - commaIndex - 1);
            } else if (isName(currString)) {
                return true;
            } else if (isValidAttribute(currString)) {
                return true;
            } else {
                return false;
            }
        }

        return false;
    }
    return false;
}

bool Tokenizer::isValidAttribute(std::string s) {
    std::unordered_set<std::string> attributeNameList = {"procName", "varName", "value", "stmt#"};
    size_t fullstopIndex = s.find('.');
    std::string synonymName = s.substr(0, fullstopIndex);
    std::string attributeName = s.substr(fullstopIndex + 1, s.length() - fullstopIndex - 1);
    if (!isName(synonymName)) {
        return false;
    }
    if (!attributeNameList.count(attributeName)) {
        return false;
    }
    return true;
}

std::vector<std::string> Tokenizer::getValidAttribute(std::string s) {
    std::vector<std::string> attribute = {};
    std::unordered_set<std::string> attributeNameList = {"procName", "varName", "value", "stmt#"};
    size_t fullstopIndex = s.find('.');
    std::string synonymName = s.substr(0, fullstopIndex);
    std::string attributeName = s.substr(fullstopIndex + 1, s.length() - fullstopIndex - 1);
    if (isName(synonymName) && attributeNameList.count(attributeName)) {
        return {synonymName, attributeName};
    } else {
        return attribute;
    }
}

/**
 * Tokenizes each character or string according to Token Types and outputs vector<TokenObject>
 */
std::vector<TokenObject> Tokenizer::tokenize(std::string query) {
    std::vector<TokenObject> tokenList;
    std::vector<std::string> tokenValues = splitQuery(query);

    // Remove empty strings from tokenized values
    tokenValues.erase(std::remove_if(tokenValues.begin(), tokenValues.end(), isEmptyOrBlank), tokenValues.end());

    // Remove empty spaces within tokenized values
    for (auto &s : tokenValues) {
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    }
    for (std::string s : tokenValues) {
        s = trimString(s);
        if (stringToTokenMap.find(s) != stringToTokenMap.end()) {
            TokenObject object = TokenObject(stringToTokenMap[s], s);
            tokenList.push_back(object);
        } else {
            if (isTuple(s)) {
                TokenObject object = TokenObject(TokenType::TUPLE, s);
                tokenList.push_back(object);
            } else if (isValidAttribute(s)) {
                TokenObject object = TokenObject(TokenType::ATTRIBUTE, s);
                tokenList.push_back(object);
            } else if (isName(s)) {
                TokenObject object = TokenObject(TokenType::NAME, s);
                tokenList.push_back(object);
            } else if (isInteger(s)) {
                TokenObject object = TokenObject(TokenType::INTEGER, s);
                tokenList.push_back(object);
            } else if (isIdentity(s)) {
                std::string trimmedQuotesFromIdentity = trimQuotesOrWildcard(s);
                TokenObject object = TokenObject(TokenType::NAME_WITH_QUOTATION, trimmedQuotesFromIdentity);
                tokenList.push_back(object);
            } else if (isExpression(s)) {
                // Return trimmed string
                std::string trimmedQuotesFromExpression = trimQuotesOrWildcard(s);
                TokenObject object = TokenObject(TokenType::EXPRESSION, trimmedQuotesFromExpression);
                tokenList.push_back(object);
            } else if (isSubExpression(s)) {
                std::string trimmedQuotesFromSubExpression = trimQuotesOrWildcard(s);
                std::string trimmedWildcardAndQuotesFromSubExpression = trimQuotesOrWildcard(trimmedQuotesFromSubExpression);
                TokenObject object = TokenObject(TokenType::SUBEXPRESSION, trimmedWildcardAndQuotesFromSubExpression);
                tokenList.push_back(object);
            } else {
                throw TokenException();
            }
        }
    }
    return tokenList;
}





