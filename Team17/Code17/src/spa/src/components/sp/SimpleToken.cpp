#include "SimpleToken.h"

SimpleToken::SimpleToken(SpTokenType type, std::string value, int statementNumber) {
    this->type = type;
    this->value = value;
    this->statementNumber = statementNumber;
}

void SimpleToken::setChildren(std::vector<SimpleToken> children) {
    this->children = children;
}

std::vector<SimpleToken> SimpleToken::getChildren() {
    return this->children;
}

