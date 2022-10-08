#pragma once

#include "../SimpleValidator.h"
#include "./ValidatorState.h"

class NestedState : public ValidatorState {
public:
    NestedState(SimpleValidator* context);
    void validLine(SpTokenType type, int statementNumber);
    bool validCode();
    void close();

private:
    SimpleValidator* context;
    bool hasStmt;

};