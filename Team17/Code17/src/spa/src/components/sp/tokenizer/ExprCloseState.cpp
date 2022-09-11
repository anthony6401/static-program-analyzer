#include "ExprCloseState.h"
#include "FactorState.h"
#include "OperandState.h"
#include "../validator/SimpleValidator.h"

ExprCloseState::ExprCloseState(ExprStack* context) {
    this->context = context;
}

void ExprCloseState::put(std::vector<SimpleToken>& children, std::string value) {
    if (SimpleValidator::validateExprOpr(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TOPR, value, 0, NULL);
        children.push_back(token);
        this->context->setState(new OperandState(this->context));
    } else if (SimpleValidator::validateConstant(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TCONSTANT, value, 0, NULL);
        children.push_back(token);
        this->context->setState(new FactorState(this->context));
    } else if (SimpleValidator::validateVariable(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TVARIABLE, value, 0, NULL);
        children.push_back(token);
        this->context->setState(new FactorState(this->context));
    } else {
        throw std::invalid_argument("Invalid character " + value);
    }
}

bool ExprCloseState::valid() {
    return true;
}
