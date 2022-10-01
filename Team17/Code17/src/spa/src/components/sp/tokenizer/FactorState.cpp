#include "FactorState.h"
#include "OperandState.h"
#include "ExprCloseState.h"
#include "../validator/SimpleValidator.h"

FactorState::FactorState(ExprStack* context) {
    this->context = context;
}

void FactorState::put(std::vector<SimpleToken>& children, std::string value) {
    if (SimpleValidator::validateExprOpr(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TOPR, value, 0);
        children.push_back(token);
        this->context->setState(new OperandState(this->context));
    } else if (value == ")") {
        this->context->close();
        this->context->setState(new ExprCloseState(this->context));
    } else {
        throw std::invalid_argument("Invalid character " + value);
    }
}

bool FactorState::valid() {
    return true;
}