#pragma once

#include "./ValidatorState.h"

class ElseState : public ValidatorState {
public:
    ElseState();
    bool validLine(SpTokenType type);
    bool validCode();
    bool isIfState();

};