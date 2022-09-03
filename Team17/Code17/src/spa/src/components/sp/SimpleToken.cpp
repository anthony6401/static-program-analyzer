#include "SimpleToken.h"

/// <summary>
/// Represent individual SIMPLE tokens
/// </summary>
/// <param name="type">type of token</param>
/// <param name="value">value of token</param>
/// <param name="statementNumber">statement number token is from</param>
/// <param name="parseFunction">function to parse token for design extractor</param>
SimpleToken::SimpleToken(TokenType type, std::string value,
        int statementNumber, void (*parseFunction)(SimpleToken&, std::vector<std::string>&)) {
    this->type = type;
    this->value = value;
    this->statementNumber = statementNumber;
    this->parseFunction = parseFunction;
}

/// <summary>
/// set the child tokens in AST of token
/// </summary>
/// <param name="children">child tokens in evaluation order</param>
void SimpleToken::setChildren(std::vector<SimpleToken> children) {
    this->children = children;
}

/// <summary>
/// return child tokens in AST of token
/// </summary>
/// <returns>child tokens in evaluation order</returns>
std::vector<SimpleToken> SimpleToken::getChildren() {
    return this->children;
}
