#include "ExprCloseState.h"
#include "FactorState.h"
#include "OperandState.h"
#include "../../validator/SimpleValidator.h"

ExprCloseState::ExprCloseState(ExprStack* context) {
    this->context = context;
}

void ExprCloseState::put(std::vector<SimpleToken>& children, std::string value) {
    if (SimpleValidator::isValidExprOpr(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TOPR, value, 0);
        children.push_back(token);
        this->context->setState(new OperandState(this->context));
    } else if (value == ")") {
        this->context->close();
    } else {
        throw std::invalid_argument("Invalid character " + value);
    }
}

bool ExprCloseState::valid() {
    return true;
}
