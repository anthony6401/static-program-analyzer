#pragma once

#include "../../SimpleToken.h"

class ValidatorState {
public:
    virtual bool validLine(SpTokenType type) { return false; }
    virtual bool validCode() { return false; }
    virtual bool isIfState() { return false; }
};