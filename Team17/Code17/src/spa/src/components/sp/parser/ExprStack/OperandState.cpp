#include "OperandState.h"
#include "FactorState.h"
#include "../../validator/SimpleValidator.h"

OperandState::OperandState(ExprStack* context) {
    this->context = context;
}

void OperandState::put(std::vector<SimpleToken>& children, std::string value) {
    if (SimpleValidator::isValidConstant(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TCONSTANT, value, 0);
        children.push_back(token);
        this->context->setState(new FactorState(this->context));
    } else if (SimpleValidator::isValidVariable(value)) {
        SimpleToken token = SimpleToken(SpTokenType::TVARIABLE, value, 0);
        children.push_back(token);
        this->context->setState(new FactorState(this->context));
    } else if (value == "(") {
        this->context->open();
    } else {
        throw std::invalid_argument("Invalid character " + value);
    }
}

bool OperandState::valid() {
    return false;
}
