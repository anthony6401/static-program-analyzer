#include "./IfState.h"
#include "./ElseState.h"
#include <stdexcept>

IfState::IfState(SimpleValidator* context) {
    this->context = context;
    expectElse = true;
}

void IfState::validLine(SpTokenType type, int statementNumber) {
    if (type == SpTokenType::TPROCEDURE || type == SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Expected Normal::" + std::to_string(statementNumber));
    }
}

bool IfState::validCode() {
    return false;
}

void IfState::close() {
    if (expectElse) {
        expectElse = false;
        context->setState(new ElseState(context));
    } else {
        context->state = context->parentStates.top();
        context->parentStates.pop();
        delete this;
    }
}