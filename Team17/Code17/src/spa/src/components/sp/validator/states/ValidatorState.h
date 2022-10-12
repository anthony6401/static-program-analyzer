#pragma once

#include "../../SimpleToken.h"

class SimpleValidator;

class ValidatorState {
public:
    virtual void validLine(SpTokenType type, int statementNumber) {}
    virtual bool validCode() { return false; }
    virtual void close() = 0;
    bool hasStmt = false;

};