#pragma once

#include "../SimpleValidator.h"
#include "./ValidatorState.h"

class IfState : public ValidatorState {
public:
    IfState(SimpleValidator* context);
    void validateLine(SpTokenType type, int statementNumber);
    bool isValidCode();
    void close();

private:
    SimpleValidator* context;
    bool expectElse;
    bool hasStmt;

};