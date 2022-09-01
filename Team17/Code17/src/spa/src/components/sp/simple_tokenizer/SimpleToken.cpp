#include "SimpleToken.h"

SimpleToken::SimpleToken(TokenType type, std::string value) {
    this->type = type;
    this->value = value;
}

void SimpleToken::setChilds(std::vector<SimpleToken*> childs) {
    this->childs = childs;
}

std::vector<SimpleToken*> SimpleToken::getChilds() {
    return this->childs;
}