#include "./NestedState.h"
#include <stdexcept>

NestedState::NestedState(SimpleValidator* context) {
    this->context = context;
}

void NestedState::validLine(SpTokenType type, int statementNumber) {
    if (type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Unexpected procedure::" + std::to_string(statementNumber));
    } else if (type == SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Unexpected else::" + std::to_string(statementNumber));
    } 
}

bool NestedState::validCode() {
    return false;
}

void NestedState::close() {
    context->state = context->parentStates.top();
    context->parentStates.pop();
    delete this;
}