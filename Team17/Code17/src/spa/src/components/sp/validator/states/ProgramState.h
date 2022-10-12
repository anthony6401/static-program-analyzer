#pragma once

#include "./ValidatorState.h"
#include "../SimpleValidator.h"

class ProgramState : public ValidatorState {
public:
    ProgramState(SimpleValidator* context);
    void validateLine(SpTokenType type, int statementNumber);
    bool isValidCode();
    void close();

private:
    SimpleValidator* context;
    bool hasStmt;

};