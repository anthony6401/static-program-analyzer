#include "ExprStack.h"
#include "OperandState.h"
#include <iostream>

ExprStack::ExprStack() {
    this->state = new OperandState(this);
}

void ExprStack::setState(ExprState* newState) {
    delete this->state;
    this->state = newState;
}

void ExprStack::open() {
    this->bracketStack.push("(");
}

void ExprStack::close() {
    if (bracketStack.size() > 0) {
        this->bracketStack.pop();
    } else {
        throw std::invalid_argument("Unexpected )");
    }
}

void ExprStack::put(std::string value) {
    this->state->put(children, value);
}

bool ExprStack::valid() {
    return this->state->valid() && this->bracketStack.size() == 0;
}

std::vector<SimpleToken> ExprStack::get() {
    return this->children;
}
