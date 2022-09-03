#include "SimpleToken.h"

SimpleToken::SimpleToken(TokenType type, std::string value,
        int statementNumber, void (*parseFunction)(SimpleToken&, std::vector<std::string>&)) {
    this->type = type;
    this->value = value;
    this->statementNumber = statementNumber;
    this->parseFunction = parseFunction;
}

void SimpleToken::setChildren(std::vector<SimpleToken*> children) {
    this->children = children;
}

std::vector<SimpleToken*> SimpleToken::getChildren() {
    return this->children;
}
