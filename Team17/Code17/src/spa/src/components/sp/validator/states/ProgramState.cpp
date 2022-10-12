#include "./ProgramState.h"
#include "NestedState.h"
#include <stdexcept>

ProgramState::ProgramState(SimpleValidator* context) {
    this->context = context;
    this->hasStmt = false;
}

void ProgramState::validateLine(SpTokenType type, int statementNumber) {
    if (type != SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Expected Procedure::" + std::to_string(statementNumber));
    }
    this->hasStmt = true;
}

bool ProgramState::isValidCode() {
    return hasStmt;
}

void ProgramState::close() {
    throw std::invalid_argument("Received invalid SIMPLE code line. Expected procedure");
}
