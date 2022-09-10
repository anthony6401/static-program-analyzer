#pragma once

#include "ExprState.h"
#include "ExprStack.h"

class ExprCloseState : public ExprState {
public:
    ExprCloseState(ExprStack* context);
    void put(std::vector<SimpleToken>& children, std::string value);
    bool valid();

private:
    ExprStack* context;

};
