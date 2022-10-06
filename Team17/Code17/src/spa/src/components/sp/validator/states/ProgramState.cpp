#include "./ProgramState.h"
#include "NestedState.h"
#include <stdexcept>

ProgramState::ProgramState(SimpleValidator* context) {
    this->context = context;
}

void ProgramState::validLine(SpTokenType type, int statementNumber) {
    if (type != SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line. Expected Procedure::" + std::to_string(statementNumber));
    }
}

bool ProgramState::validCode() {
    return true;
}

void ProgramState::close() {
    throw std::invalid_argument("Received invalid SIMPLE code line. Expected procedure");
}
