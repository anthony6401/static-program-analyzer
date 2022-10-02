#include "./NestedState.h"

NestedState::NestedState() {}

bool NestedState::validLine(SpTokenType type) {
    return type != SpTokenType::TPROCEDURE && type != SpTokenType::TELSE;
}

bool NestedState::validCode() {
    return false;
}

bool NestedState::isIfState() {
    return false;
}