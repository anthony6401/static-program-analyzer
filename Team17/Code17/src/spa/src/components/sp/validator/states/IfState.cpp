#include "./IfState.h"
#include "./ElseState.h"
#include <stdexcept>

IfState::IfState(SimpleValidator* context) {
    this->context = context;
    expectElse = true;
    this->hasStmt = false;
}

void IfState::validLine(SpTokenType type, int statementNumber) {
    hasStmt = true;
    if (type == SpTokenType::TPROCEDURE || type == SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Expected Normal::" + std::to_string(statementNumber));
    }
}

bool IfState::validCode() {
    return false;
}

void IfState::close() {
    if (expectElse) {
        if (hasStmt) {
            expectElse = false;
            hasStmt = false;
            context->setState(new ElseState(context));
        } else {
            throw std::invalid_argument("No stmts where expected");
        }
    } else {
        context->state = context->parentStates.top();
        context->parentStates.pop();
        delete this;
    }
}