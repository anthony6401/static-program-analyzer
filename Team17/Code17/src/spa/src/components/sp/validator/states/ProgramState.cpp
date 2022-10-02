#include "./ProgramState.h"

ProgramState::ProgramState() {}

bool ProgramState::validLine(SpTokenType type) {
    return type != SpTokenType::TPROCEDURE;
}

bool ProgramState::validCode() {
    return true;
}

bool ProgramState::isIfState() {
    return false;
}