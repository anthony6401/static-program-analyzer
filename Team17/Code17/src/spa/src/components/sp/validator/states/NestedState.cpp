#include "./NestedState.h"
#include <stdexcept>

NestedState::NestedState(SimpleValidator* context) {
    this->context = context;
    hasStmt = false;
}

void NestedState::validateLine(SpTokenType type, int statementNumber) {
    hasStmt = true;
    if (type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Unexpected procedure::" + std::to_string(statementNumber));
    } else if (type == SpTokenType::TELSE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Unexpected else::" + std::to_string(statementNumber));
    } 
}

bool NestedState::isValidCode() {
    return false;
}

void NestedState::close() {
    if (hasStmt) {
        context->state = context->parentStates.top();
        context->parentStates.pop();
        delete this;
    } else {
        throw std::invalid_argument("No stmts where expected");
    }

}