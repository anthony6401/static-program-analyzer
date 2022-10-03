#include "./IfState.h"

IfState::IfState() {}

bool IfState::validLine(SpTokenType type) {
    return type != SpTokenType::TPROCEDURE && type != SpTokenType::TELSE;
}

bool IfState::validCode() {
    return false;
}

bool IfState::isIfState() {
    return true;
}