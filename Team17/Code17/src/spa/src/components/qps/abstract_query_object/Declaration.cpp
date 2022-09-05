#include "Declaration.h"

Declaration::Declaration(qps::TokenType entity, std::string name) {
    this->entity = entity;
    this->name = name;
}

TokenType Declaration::getEntityType() {
    return this->entity;
}

std::string Declaration::getName() {
    return this->name;
}