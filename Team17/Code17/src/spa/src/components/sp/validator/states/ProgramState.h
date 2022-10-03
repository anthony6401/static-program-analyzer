#pragma once

#include "./ValidatorState.h"
#include "../SimpleValidator.h"

class ProgramState : public ValidatorState {
public:
    ProgramState(SimpleValidator* context);
    void validLine(SpTokenType type, int statementNumber);
    bool validCode();
    void close();

private:
    SimpleValidator* context;

};