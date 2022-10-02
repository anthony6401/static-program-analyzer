#pragma once

#include "./ValidatorState.h"

class NestedState : public ValidatorState {
public:
    NestedState();
    bool validLine(SpTokenType type);
    bool validCode();
    bool isIfState();

};