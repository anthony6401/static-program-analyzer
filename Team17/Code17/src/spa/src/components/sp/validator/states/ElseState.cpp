#include "./ElseState.h"
#include <stdexcept>

ElseState::ElseState(SimpleValidator* context) {
    this->context = context;
    this->hasStmt = true;
}

void ElseState::validateLine(SpTokenType type, int statementNumber) {
    if (type != SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Expected Else::" + std::to_string(statementNumber));
    }
}

bool ElseState::isValidCode() {
    return false;
}

void ElseState::close() {
    context->state = context->parentStates.top();
    context->parentStates.pop();
    delete this;
}