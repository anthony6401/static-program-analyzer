#include "./IfState.h"
#include "./ElseState.h"
#include <stdexcept>

IfState::IfState(SimpleValidator* context) {
    this->context = context;
    expectElse = true;
    this->hasStmt = false;
}

void IfState::validateLine(SpTokenType type, int statementNumber) {
    hasStmt = true;
    if (type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Unexpected procedure::" + std::to_string(statementNumber));
    }
    else if (type == SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Unexpected else::" + std::to_string(statementNumber));
    }
}

bool IfState::isValidCode() {
    return false;
}

void IfState::close() {
    if (!hasStmt) {
        throw std::invalid_argument("No stmts where expected");
    }
    if (expectElse) {
        expectElse = false;
        hasStmt = false;
        context->setState(new ElseState(context));
    } else {
        context->state = context->parentStates.top();
        context->parentStates.pop();
        delete this;
    }
}