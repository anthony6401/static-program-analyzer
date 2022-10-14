#pragma once

#include "../SimpleValidator.h"
#include "./ValidatorState.h"

class ElseState : public ValidatorState {
public:
    ElseState(SimpleValidator* context);
    void validateLine(SpTokenType type, int statementNumber);
    bool isValidCode();
    void close();

private:
    SimpleValidator* context;
    bool hasStmt;

};