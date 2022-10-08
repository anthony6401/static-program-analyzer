#pragma once

#include "../SimpleValidator.h"
#include "./ValidatorState.h"

class IfState : public ValidatorState {
public:
    IfState(SimpleValidator* context);
    void validLine(SpTokenType type, int statementNumber);
    bool validCode();
    void close();

private:
    SimpleValidator* context;
    bool expectElse;
    bool hasStmt;

};