#include "./ElseState.h"
#include <stdexcept>

ElseState::ElseState(SimpleValidator* context) {
    this->context = context;
}

void ElseState::validLine(SpTokenType type, int statementNumber) {
    if (type != SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Expected Else::" + std::to_string(statementNumber));
    }
}

bool ElseState::validCode() {
    return false;
}

void ElseState::close() {
    context->state = context->parentStates.top();
    context->parentStates.pop();
    delete this;
}