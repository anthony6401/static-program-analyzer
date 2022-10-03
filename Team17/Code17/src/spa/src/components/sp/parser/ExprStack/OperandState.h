#pragma once

#include "ExprState.h"

class ExprStack;

class OperandState : public ExprState {
public:
    OperandState(ExprStack* context);
    void put(std::vector<SimpleToken>& children, std::string value);
    bool valid();

private:
    ExprStack* context;

};
