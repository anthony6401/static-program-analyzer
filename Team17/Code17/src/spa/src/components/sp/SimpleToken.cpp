#include "SimpleToken.h"

SimpleToken::SimpleToken(TokenType type, std::string value, int statementNumber) {
    this->type = type;
    this->value = value;
    this->statementNumber = statementNumber
}

void SimpleToken::setChilds(std::vector<SimpleToken*> childs) {
    this->childs = childs;
}

std::vector<SimpleToken*> SimpleToken::getChilds() {
    return this->childs;
}

