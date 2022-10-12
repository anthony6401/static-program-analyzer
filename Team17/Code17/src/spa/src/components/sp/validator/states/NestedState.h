#pragma once

#include "../SimpleValidator.h"
#include "./ValidatorState.h"

class NestedState : public ValidatorState {
public:
    NestedState(SimpleValidator* context);
    void validateLine(SpTokenType type, int statementNumber);
    bool isValidCode();
    void close();

private:
    SimpleValidator* context;
    bool hasStmt;

};