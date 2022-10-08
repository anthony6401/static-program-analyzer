#pragma once

#include "../SimpleValidator.h"
#include "./ValidatorState.h"

class ElseState : public ValidatorState {
public:
    ElseState(SimpleValidator* context);
    void validLine(SpTokenType type, int statementNumber);
    bool validCode();
    void close();

private:
    SimpleValidator* context;
    bool hasStmt;

};