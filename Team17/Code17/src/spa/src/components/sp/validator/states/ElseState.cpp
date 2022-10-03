#include "./ElseState.h"

ElseState::ElseState() {}

bool ElseState::validLine(SpTokenType type) {
    return type == SpTokenType::TELSE;
}

bool ElseState::validCode() {
    return false;
}

bool ElseState::isIfState() {
    return false;
}