#pragma once

#include "./ValidatorState.h"

class IfState : public ValidatorState {
public:
    IfState();
    bool validLine(SpTokenType type);
    bool validCode();
    bool isIfState();

};