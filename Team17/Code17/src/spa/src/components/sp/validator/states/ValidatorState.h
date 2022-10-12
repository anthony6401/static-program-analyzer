#pragma once

#include "../../SimpleToken.h"

class SimpleValidator;

class ValidatorState {
public:
    virtual void validateLine(SpTokenType type, int statementNumber) {}
    virtual bool isValidCode() { return false; }
    virtual void close() = 0;

private:
    bool hasStmt = false;

};