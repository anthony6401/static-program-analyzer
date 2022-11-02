#include "Tokenizer.h"
#include "../exceptions/TokenException.h"
#include "TokenType.h"
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace qps;

std::string whitespace = "\n\r\t\f\v";
std::unordered_set<char> expressionSymbolsAndBrackets = {'(', ')', '+', '-',
                                                         '*', '/', '%'};
std::unordered_set<std::string> expressionSymbols = {"+", "-", "*", "/", "%"};
std::unordered_set<std::string> attributeNameList = {"procName", "varName",
                                                     "value", "stmt#"};
std::vector<char> emptyCharVector = {' ', '\n', '\t', '\v', '\f', '\r'};

Tokenizer::Tokenizer() {
  stringToTokenMap = {{"Select", TokenType::SELECT},
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
                      {"procedure", TokenType::PROCEDURE}};
}

std::vector<std::string> formatCharToStringVector(const std::string &s,
                                                  char delimiter) {
  std::vector<std::string> tokenValueString;
  std::stringstream ss(s);
  std::string tokenValue;

  while (getline(ss, tokenValue, delimiter)) {
    tokenValueString.push_back(tokenValue);
  }

  return tokenValueString;
}

bool charTypeToggler(bool isCharType) { return !isCharType; }

bool isEmptySpace(char character) {
  bool isEmpty =
      std::count(emptyCharVector.begin(), emptyCharVector.end(), character);
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

std::vector<std::string> splitQuery(const std::string &query) {
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
    default:
      break;
    }

    if (c != ' ' && !isEmptySpace(c)) {
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
    default:
      break;
    }
  }

  std::string stringOutput =
      std::string(char_output.begin(), char_output.end());
  std::vector<std::string> splitQuery =
      formatCharToStringVector(stringOutput, delimiter);
  return splitQuery;
}

std::string trimString(const std::string &s) {
  const auto beginning = s.find_first_not_of(whitespace);
  const auto ending = s.find_last_not_of(whitespace);
  const auto range = ending - beginning + 2;
  return s.substr(beginning, range);
}

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

std::string trimQuotesOrWildcard(const std::string &s) {
  return s.substr(1, s.size() - 2);
}

bool Tokenizer::isIdentity(std::string s) {
  if (s.size() <= 2) {
    return false;
  }

  s = trimString(s);
  if (s.front() == '"' && s.back() == '"') {
    if (isName(trimQuotesOrWildcard(s))) {
      return true;
    }
  }
  return false;
}

void Tokenizer::symbolsFoundHandler(std::string &temp,
                                    std::vector<std::string> &expressionTokens,
                                    bool &isInvalidExpression) {
  std::vector<std::string> invalidExpression;
  std::string tempString = temp;
  if (!temp.empty()) {
    if (isName(tempString) || isInteger(tempString)) {
      expressionTokens.push_back(temp);
      temp.clear();
    } else {
      isInvalidExpression = true;
    }
  }
}

void Tokenizer::characterInExpressionHandler(
    char character, std::string &temp,
    std::vector<std::string> &expressionTokens, bool &isInvalidExpression) {
  auto symbolsIterator = expressionSymbolsAndBrackets.find(character);
  if (symbolsIterator == expressionSymbolsAndBrackets.cend()) {
    temp.push_back(character);
  } else {
    symbolsFoundHandler(temp, expressionTokens, isInvalidExpression);
    expressionTokens.emplace_back(1, character);
  }
}

std::vector<std::string>
Tokenizer::convertExpressionToStringVector(const std::string &s) {
  std::vector<std::string> invalidExpression;
  std::vector<std::string> expressionTokens;

  bool isInvalidExpression = false;
  std::string temp;
  for (char character : s) {
    characterInExpressionHandler(character, temp, expressionTokens,
                                 isInvalidExpression);
    if (isInvalidExpression) {
      return invalidExpression;
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

void openBracketInExpressionVectorHandler(
    std::string &prev, bool &isPrevName, bool &isPrevInteger,
    std::stack<std::string> &expressionStack, bool &returnFalse) {
  if (isPrevInteger || isPrevName) {
    returnFalse = true;
  }
  expressionStack.push("(");
  prev = "(";
  isPrevInteger = false;
  isPrevName = false;
}

void closedBracketInExpressionVectorHandler(
    std::string &prev, bool &isPrevName, bool &isPrevInteger,
    std::stack<std::string> &expressionStack, bool &returnFalse) {
  if (expressionStack.empty() || expressionStack.top() != "(" ||
      expressionSymbols.count(prev) || prev == "(") {
    returnFalse = true;
  } else {
    expressionStack.pop();
    prev = ")";
  }
  isPrevInteger = false;
  isPrevName = false;
}

void Tokenizer::nonBracketInExpressionVectorHandler(
    std::string &string, std::string &prev, bool &isPrevName,
    bool &isPrevInteger, std::stack<std::string> &expressionStack,
    bool &returnFalse) {
  if (isName(string)) {
    if (isPrevName) {
      returnFalse = true;
    } else {
      isPrevName = true;
      prev = string;
    }
  } else if (isInteger(string)) {
    if (isPrevInteger) {
      returnFalse = true;
    } else {
      isPrevInteger = true;
      prev = string;
    }
  } else if (expressionSymbols.count(string)) {
    if (expressionSymbols.count(prev) || prev == "(" || prev.empty()) {
      returnFalse = true;
    }
    prev = string;
    isPrevInteger = false;
    isPrevName = false;
  }
}

void Tokenizer::stringInExpressionVectorHandler(
    std::string &string, std::string &prev, bool &isPrevName,
    bool &isPrevInteger, std::stack<std::string> &expressionStack,
    bool &returnFalse) {
  if (string == "(") {
    openBracketInExpressionVectorHandler(prev, isPrevName, isPrevInteger,
                                         expressionStack, returnFalse);
  } else if (string == ")") {
    closedBracketInExpressionVectorHandler(prev, isPrevName, isPrevInteger,
                                           expressionStack, returnFalse);
  } else {
    Tokenizer::nonBracketInExpressionVectorHandler(
        string, prev, isPrevName, isPrevInteger, expressionStack, returnFalse);
  }
}

bool Tokenizer::validateExpression(std::vector<std::string> expressionVector) {
  std::stack<std::string> expressionStack;
  std::string prev;
  bool returnFalse = false;
  bool isPrevName = false;
  bool isPrevInteger = false;
  for (const auto &string : expressionVector) {
    stringInExpressionVectorHandler(const_cast<std::string &>(string), prev,
                                    isPrevName, isPrevInteger, expressionStack,
                                    returnFalse);
    if (returnFalse) {
      return false;
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

bool Tokenizer::isExpression(std::string s) {
  if (s.size() < 3) {
    return false;
  }
  if (s.front() != '"' || s.back() != '"') {
    return false;
  }

  if (s.front() == '"' && s.back() == '"') {
    std::string trimmedQuotes = trimQuotesOrWildcard(s);
    std::vector<std::string> expressionVector =
        convertExpressionToStringVector(trimmedQuotes);

    if (expressionVector.empty()) {
      return false;
    } else {
      bool isValidExpression = validateExpression(expressionVector);
      return isValidExpression;
    }
  }
  return false;
}

bool Tokenizer::isSubExpression(std::string s) {
  if (s.size() < 5) {
    return false;
  }

  if (s.front() == '_' && s.back() == '_') {
    std::string withoutWildcard = trimQuotesOrWildcard(s);
    bool isIdentity = Tokenizer::isIdentity(withoutWildcard);
    bool isExpression = Tokenizer::isExpression(withoutWildcard);
    if (isIdentity || isExpression) {
      return true;
    }
  }

  return false;
}

auto isEmptyOrBlank = [](const std::string &s) {
  return s.find_first_not_of(" \n\t\f\v\r") == std::string::npos;
};

void Tokenizer::validateTupleValueHandler(std::string &currString,
                                          std::string &currValue,
                                          size_t commaIndex,
                                          bool &returnFalse) {
  currValue = currString.substr(0, commaIndex);

  if (!isName(currValue) && !isValidAttribute(currValue)) {
    returnFalse = true;
  }

  currString =
      currString.substr(commaIndex + 1, currString.length() - commaIndex - 1);
}

bool Tokenizer::isValidTuple(std::string &currString, std::string &currValue) {
  bool returnFalse = false;
  while (currString.length() > 0 && !returnFalse) {
    size_t commaIndex = currString.find(',');
    if (commaIndex != std::string::npos && commaIndex > 0) {
      validateTupleValueHandler(currString, currValue, commaIndex, returnFalse);
    } else if (isName(currString) || isValidAttribute(currString)) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool Tokenizer::isTuple(std::string s) {
  if (s.front() == '<' && s.back() == '>') {
    std::string currString = s.substr(1, s.length() - 2);
    std::string currValue;
    while (currString.length() > 0) {
      bool isTuple = isValidTuple(currString, currValue);
      return isTuple;
    }

    return false;
  }
  return false;
}

bool Tokenizer::isValidAttribute(std::string s) {

  size_t fullstopIndex = s.find('.');
  if (fullstopIndex == std::string::npos) {
    return false;
  }
  std::string synonymName = s.substr(0, fullstopIndex);
  std::string attributeName =
      s.substr(fullstopIndex + 1, s.length() - fullstopIndex - 1);
  if (!isName(synonymName)) {
    return false;
  }
  if (!attributeNameList.count(attributeName)) {
    return false;
  }
  return true;
}

std::vector<TokenObject> Tokenizer::tokenize(std::string &query) {
  std::vector<TokenObject> tokenList;
  std::vector<std::string> tokenValues = splitQuery(query);

  // Remove empty strings from tokenized values
  tokenValues.erase(
      std::remove_if(tokenValues.begin(), tokenValues.end(), isEmptyOrBlank),
      tokenValues.end());

  // Remove empty spaces within tokenized values
  for (auto &s : tokenValues) {
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
  }

  for (std::string s : tokenValues) {
    s = trimString(s);
    if (stringToTokenMap.find(s) != stringToTokenMap.end()) {
      TokenObject object = TokenObject(stringToTokenMap[s], s);
      tokenList.push_back(object);
    } else if (isTuple(s)) {
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
      TokenObject object = TokenObject(TokenType::NAME_WITH_QUOTATION,
                                       trimmedQuotesFromIdentity);
      tokenList.push_back(object);
    } else if (isExpression(s)) {
      std::string trimmedQuotesFromExpression = trimQuotesOrWildcard(s);
      TokenObject object =
          TokenObject(TokenType::EXPRESSION, trimmedQuotesFromExpression);
      tokenList.push_back(object);
    } else if (isSubExpression(s)) {
      std::string trimmedQuotesFromSubExpression = trimQuotesOrWildcard(s);
      std::string trimmedWildcardAndQuotesFromSubExpression =
          trimQuotesOrWildcard(trimmedQuotesFromSubExpression);
      TokenObject object = TokenObject(
          TokenType::SUBEXPRESSION, trimmedWildcardAndQuotesFromSubExpression);
      tokenList.push_back(object);
    } else {
      throw TokenException();
    }
  }
  return tokenList;
}
