#pragma once

#include "./ValidatorState.h"

class ProgramState : public ValidatorState {
public:
    ProgramState();
    bool validLine(SpTokenType type);
    bool validCode();
    bool isIfState();

};